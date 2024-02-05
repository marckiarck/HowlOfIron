// Fill out your copyright notice in the Description page of Project Settings.


#include "HIWerewolf.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Characters/HICharacterAttributes.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"
#include "Game/HIGameInstance.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayTagContainer.h"
#include "Game/DataTable/HIWerewolfDatatable.h"
#include "Game/HICameraManager.h"
#include "Game/HIGameData.h"
#include "Game/PerceptionSystem/HIDetectableActorComponent.h"
#include "GAS/Structs/HIFGameplayEventData.h"
#include "HIMacros.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MapLogic/HITeleportPawn.h"
#include "MapLogic/HIWall.h"
#include "UI/HIButtonHUD.h"
#include "HowlOfIron/MapLogic/HIAnchorage.h"

AHIWerewolf::AHIWerewolf() :
    distanceToWallToClimbFromFloor(1000.f),
    distanceToWallToClimbFromBuilding(1500.f),
    climbingSpeed(200.f),
    targetWall(nullptr),
    isClimbing(false),
    isDoingFinisher(false),
    distanceToBordersToJump(150.f),
    distanceToBuildingToJump(1500.f),
    topExecutionCapsuleRadius(300.f),
    topExecutionCapsuleHeight(2000.f),
    timerEQS(0.05f),
    enemygrabbed(nullptr),
    debugBarsVisible(false)
{
    PrimaryActorTick.bCanEverTick = false;

    UCapsuleComponent* capsule = GetCapsuleComponent();
    SetRootComponent(capsule);

    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...

    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    springArm->SetupAttachment(capsule);
    springArm->bUsePawnControlRotation = true;

    cineCamera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("CineCamera"));
    cineCamera->SetupAttachment(springArm, USpringArmComponent::SocketName);
    cineCamera->bUsePawnControlRotation = false;

    smokesComponentIz = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SmokeIz"));
    smokesComponentIz->SetupAttachment(GetMesh(), TEXT("Chestjnt_SteamSocket_Leftt"));

    smokesComponentDe = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SmokeDe"));
    smokesComponentDe->SetupAttachment(GetMesh(), TEXT("Chestjnt_SteamSocket"));

    comboSystem = CreateDefaultSubobject<UHIComboManagerComponent>(TEXT("ComboComponent"));

    physicAnimComponent = CreateDefaultSubobject<UPhysicalAnimationComponent>(TEXT("PhysicalAnimationComponent"));

    attributes = CreateDefaultSubobject<UHIWerewolfAttributes>(TEXT("Attributes"));

    OnActorHit.AddDynamic(this, &AHIWerewolf::OnHitBegin);

    CreateDefaultSubobject<UHIDetectableActorComponent>(TEXT("DetectableActorComponent"));

    UHIGameData::HISetPlayerWerewolf(this);

    HISetCharacterType(WEREWOLF);
}

void AHIWerewolf::BeginPlay()
{
    Super::BeginPlay();

    SetGameplayEffectsReferences();
    SetInitialValues();
    GetMesh()->SetAllBodiesBelowSimulatePhysics("Hips", true, false);

    //Show current mission if any
    UHIGameInstance* GI = Cast<UHIGameInstance>(GetGameInstance());
    GI->gameManager->ShowMission();

    if (!Cast<UHIGameInstance>(GetGameInstance())->testing)
    {
        FGameplayTagContainer bloquedImputTags;
        GET_BLOCK_INPUT_TAGS(bloquedImputTags);
        abilitySystem->AddLooseGameplayTags(bloquedImputTags);

        //to stop the wolf in the air until the game loads. Don't judge me
        GetCapsuleComponent()->SetSimulatePhysics(true);
    }

    smokesComponentDe->SetAsset(smokesForRage[0]);
    smokesComponentIz->SetAsset(smokesForRage[0]);

    if (widgetref)
    {
        widgetref->debugBars->SetVisibility(debugBarsVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }


}

void AHIWerewolf::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Healing



    HIHealingRegeneration(DeltaTime);


    HIUpdateEQSQueryPosition(DeltaTime);

    // ** FINISHER **
    // Ray to check if there is an enemy to finisher
    if (!TopExecution())
    {
        // ** JUMP TO CLIMB **
        // Ray from the camera to the buildings
        if (!JumpBetweenBuildings())
        {
            if (!JumpToClimb())
            {
                CANCEL_JUMP;

                if (!SameLevelExecution())
                {
                    CombatFinisher();
                }

            }
        }
    }
}

void AHIWerewolf::HIUpdateEQSQueryPosition(float DeltaTime)
{
    FVector oldPosition = UHIGameData::HIGetWerewolfEQSPosition();
    FVector newPosition = GetActorLocation();

    if (FVector::Dist(oldPosition, newPosition) >= 500.f)
    {
        UHIGameData::HISetWerewolfEQSPosition(newPosition);
    }
    else
    {
        if (elapsedtimerEQS >= timerEQS)
        {

            // 			if (FVector::Dist(oldPosition, newPosition) >= 100.f)
            // 			{
            UHIGameData::HISetWerewolfEQSPosition(newPosition);
            //}

            elapsedtimerEQS -= timerEQS;
        }
    }

    elapsedtimerEQS += DeltaTime;
}

void AHIWerewolf::HIApplyRegeneration(float DeltaTime)
{

    float auxHealing = healingTick * DeltaTime;
    RegenerationEffectRef->Modifiers.Empty();
    FGameplayModifierInfo modif = FGameplayModifierInfo();
    modif.Attribute = attributes->GethealthAttribute();

    if (!HICharacterDead())
    {
        if (attributes->Gethealth() <= startHealingHP && attributes->Gethealth() + auxHealing > startHealingHP)
        {
            modif.ModifierOp = EGameplayModOp::Override;
            modif.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(startHealingHP));
            abilitySystem->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(REGENEATION_TRIGGER_TAG));
        }
        else
        {
            modif.ModifierOp = EGameplayModOp::Additive;
            modif.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(auxHealing));
        }

        RegenerationEffectRef->Modifiers.Add(modif);
        abilitySystem->ApplyGameplayEffectToSelf(RegenerationEffectRef, 0, FGameplayEffectContextHandle());
    }
    else
    {
        abilitySystem->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(REGENEATION_TRIGGER_TAG));
    }
}

bool AHIWerewolf::HIThrowEnemyGrabbed()
{
    return DetachEnemy(enemygrabbed);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region GAS_ABILITIES

const float AHIWerewolf::HIGetMaxRage()
{
    return float(ChargedAttributteComponent->HIGetMaxChargedValue());
}

void AHIWerewolf::HIActivateDash()
{
    resultVectorInput = forwardVectorInput + sideVectorInput;
    resultVectorInput.Normalize(0.00000001f);

    dashAbilityEvent.Broadcast(dashComboAbility);
}

void AHIWerewolf::HIActivateJump()
{
    FGameplayEventData DataEvent;
    DataEvent.OptionalObject = abilityData;

    FGameplayTag tagjump = FGameplayTag::RequestGameplayTag(FName(TEXT("Werewolf.Activate.Jump")), true);
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, tagjump, DataEvent);
}

void AHIWerewolf::HIActivateHowl()
{
    howlAbilityEvent.Broadcast(howlComboAbility);
}

void AHIWerewolf::HIActivateFinisher()
{
    if (!isDoingFinisher)
    {
        FGameplayEventData DataEvent;
        DataEvent.OptionalObject = abilityData;

        if (enemyToFinisher || enemyToFinisherSameLevel)
        {
            FGameplayTag tagfinisher = FGameplayTag::RequestGameplayTag(FName(TEXT("Werewolf.Activate.Execution")), true);
            UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, tagfinisher, DataEvent);
        }
        else if (enemyToCombatFinisher)
        {
            FGameplayTag tagfinisher = FGameplayTag::RequestGameplayTag(FName(TEXT("Werewolf.Activate.Finisher")), true);
            UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, tagfinisher, DataEvent);
            enemyToCombatFinisher->GetMesh()->SetScalarParameterValueOnMaterials(FName(TEXT("Focus")), 0);

        }
    }
}

void AHIWerewolf::HIActivateLightAttack()
{
    lightAttackAbilityEvent.Broadcast(lightAttackComboAbility);
}

void AHIWerewolf::HIActivateHeavyAttack()
{
    heavyAttackAbilityEvent.Broadcast(heavyAttackComboAbility);
}

void AHIWerewolf::HIHealthChanged(const FOnAttributeChangeData& Data)
{
    widgetref->HIChangeHealth(Data.NewValue);

    if (Data.NewValue <= 0.f)
    {
        FGameplayTag tagDead = FGameplayTag::RequestGameplayTag(FName(TEXT("Character.Ability.Dead")), true);
        abilitySystem->AddLooseGameplayTag(tagDead);
    }
}

void AHIWerewolf::HIMaxHealthChanged(const FOnAttributeChangeData& Data)
{
    widgetref->HISetMaxHealth(Data.NewValue);
}

void AHIWerewolf::HIRageChanged(const FOnAttributeChangeData& Data)
{
    widgetref->HIChangeRage(Data.NewValue);


    if (currentRageLevel != 0 && Data.NewValue < 100.f)
    {
        currentRageLevel = 0;
        HINoRageActivated();

    }
    else if (currentRageLevel != 1 && Data.NewValue >= 100.f && Data.NewValue < 200.f)
    {
        currentRageLevel = 1;
        HIRage1Activated();
    }
    else if (currentRageLevel != 2 && Data.NewValue >= 200.f && Data.NewValue < 300.f)
    {
        currentRageLevel = 2;
        HIRage2Activated();
    }
    else if (currentRageLevel != 3 && Data.NewValue >= 300.f)
    {
        currentRageLevel = 3;
        HIRage3Activated();
    }
}

void AHIWerewolf::HIHowlChanged(const FOnAttributeChangeData& Data)
{
    widgetref->HIChangeHowlNum(Data.NewValue);
}

void AHIWerewolf::HIspeedChanged(const FOnAttributeChangeData& Data)
{
    GetCharacterMovement()->MaxWalkSpeed = attributes->Getspeed();
}

void AHIWerewolf::HIInitializeAbilities()
{
    comboSystem->HISetComboQueueWeight(comboAbilitiesDataAsset->maxComboWeight);
    comboSystem->HISetResetQueueCooldown(comboAbilitiesDataAsset->resetColdown);

    SetUpComboAbility(lightAttackComboAbility, lightAttackAbilityEvent, comboAbilitiesDataAsset->lightAttackConfiguration);
    SetUpComboAbility(heavyAttackComboAbility, heavyAttackAbilityEvent, comboAbilitiesDataAsset->heavyAttackConfiguration);
    SetUpComboAbility(dashComboAbility, dashAbilityEvent, comboAbilitiesDataAsset->dashConfiguration);
    SetUpComboAbility(howlComboAbility, howlAbilityEvent, comboAbilitiesDataAsset->howlConfiguration);
}

void AHIWerewolf::SetUpComboAbility(TArray<UHIComboAbility*>& comboAbilityArray, FEnqueueComboAbilityEvent& abilityEvent, FComboAbilityConfiguration& abilityConfiguration)
{
    for (TSubclassOf<UGameplayAbility> gameplayAbilityClass : abilityConfiguration.gameplayAbility)
    {
        UHIComboAbility* comboAbility = NewObject<UHIComboAbility>();
        FGameplayAbilitySpecHandle abilityHandle = abilitySystem->GiveAbility(FGameplayAbilitySpec(gameplayAbilityClass.GetDefaultObject(), 1, 0));

        comboAbility->HISetGameplayAbilityHandle(abilityHandle);
        comboAbility->HISetAbilityActivationDelay(abilityConfiguration.abilityActivationDelay);
        comboAbility->HISetAbilityPriority(abilityConfiguration.abilityPriority);
        comboAbility->HISetAbilityWeight(abilityConfiguration.abilityWeight);

        comboAbilityArray.Add(comboAbility);
    }

    comboSystem->HIAttachComboEvent(abilityEvent, abilityConfiguration.attachMode);
}

void AHIWerewolf::ActivateClimb()
{
    FGameplayEventData DataEvent;
    DataEvent.OptionalObject = abilityData;

    FGameplayTag tagclimb = FGameplayTag::RequestGameplayTag(FName(TEXT("Werewolf.Activate.Climb")), true);
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, tagclimb, DataEvent);
}

const float AHIWerewolf::HIGetRage() const
{
    return ChargedAttributteComponent->HIGetCurrentChargedValue();
}

void AHIWerewolf::HIHealingRegeneration(float DeltaTime)
{

    if (!HICharacterDead())
    {
        if (camManager->currentCamView == CameraView::HUNT)
        {
            if (attributes->Gethealth() < startHealingHP)
            {
                abilitySystem->AddLooseGameplayTag(GET_GAMEPLAY_TAG(REGENEATION_TRIGGER_TAG));
            }
            else
            {
                abilitySystem->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(REGENEATION_TRIGGER_TAG));
            }
        }
    }
    else
    {
        abilitySystem->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(REGENEATION_TRIGGER_TAG));
    }
}

#pragma endregion

bool AHIWerewolf::GetIsClimbing() const
{
    return isClimbing;
}

// Includes execution from top
bool AHIWerewolf::TopExecution()
{
    FGameplayTagContainer tagContainer;
    tagContainer.AddTag(GET_GAMEPLAY_TAG(EXECUTION_TAG));

    if (!isDoingFinisher && !isClimbing && camManager->currentCamView == CameraView::HUNT)
    {
        forwardVector = cineCamera->GetForwardVector();
        forwardVector.Z = 0.f;
        forwardVector.Normalize();
        startRay = GetActorLocation() + FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) + forwardVector * topExecutionCapsuleRadius;
        endRay = startRay + FVector(0.f, 0.f, -topExecutionCapsuleHeight);
        TArray<FHitResult> enemyHits;

        if (UHIGameData::HIGetDebugMode())
        {
            FVector capsuleCenter = FVector((startRay.X + endRay.X) / 2, (startRay.Y + endRay.Y) / 2, (startRay.Z + endRay.Z) / 2);
            DrawDebugCapsule(GetWorld(), capsuleCenter, topExecutionCapsuleHeight / 2, topExecutionCapsuleRadius, FQuat(FVector(0, 0, -1), 0), FColor::Red, false, 0.f);
        }

        isRayHit = GetWorld()->SweepMultiByChannel(enemyHits, startRay, endRay, FQuat::Identity, GAME_TRACE_ENEMY, FCollisionShape::MakeCapsule(topExecutionCapsuleRadius, topExecutionCapsuleHeight / 2));

        if (isRayHit && HIIsOnEdge() && GetVelocity().Z == 0)
        {
            float minDot = 0.f;

            if (enemyToFinisher && !abilitySystem->HasAnyMatchingGameplayTags(tagContainer))
            {
                enemyToFinisher->GetMesh()->SetScalarParameterValueOnMaterials(FName(TEXT("Focus")), 0);
                enemyToFinisher = nullptr;
            }

            for (FHitResult enemyHit : enemyHits)
            {
                // Check if the enemy is on the screen
                if (UHIGameData::HIIsPositionOnScreen(enemyHit.GetActor()->GetActorLocation()))
                {
                    // @TODO: Check difference of height and recalculate distance to the enemy
                    // Now this is to allow finisher only in different heights
                    AHIEnemy* enem = Cast<AHIEnemy>(enemyHit.GetActor());

                    if (abs(enemyHit.GetActor()->GetActorLocation().Z - GetActorLocation().Z) > 500.f &&
                        enem->HIGetDetectionValue() <= detectionExecutionThreshold)
                    {
                        // If there's another enemy to finisher, target the enemy which we are looking at
                        FVector enemyVector = enemyHit.GetActor()->GetActorLocation() - GetActorLocation();
                        enemyVector.Z = 0.f;
                        enemyVector.Normalize();

                        if (FVector::DotProduct(forwardVector, enemyVector) >= minDot)
                        {
                            minDot = FVector::DotProduct(forwardVector, enemyVector);
                            enemyToFinisher = Cast<AHIEnemy>(enemyHit.GetActor());
                        }
                    }
                }
            }
            // Activate finisher
            if (enemyToFinisher && enemyToFinisher->HIGetAttributes()->Gethealth() > 0)
            {
                //Boss special checks
                bool bossTagOwned = false;
                {
                    CHECK_HAS_TAG(enemyToFinisher->GetAbilitySystemComponent(), BOSS_TAG, bossTagOwned);
                }
                if (bossTagOwned)
                {
                    bool bossInmunityActived = false;
                    CHECK_HAS_TAG(enemyToFinisher->GetAbilitySystemComponent(), INMUNITY_TAG, bossInmunityActived);

                    if (bossInmunityActived == false)
                    {
                        enemyToFinisher = nullptr;
                        return false;
                    }
                }

                if (!abilitySystem->HasAnyMatchingGameplayTags(tagContainer))
                {
                    enemyToFinisher->GetMesh()->SetScalarParameterValueOnMaterials(FName(TEXT("Focus")), 1);
                }
                abilityData->finisherPosition = enemyToFinisher->HIGetExecutionPosition(false, abilityData->backExecution);
                ensure(jumpExecutionEffectRef);
                abilitySystem->ApplyGameplayEffectToSelf(jumpExecutionEffectRef, 0.f, FGameplayEffectContextHandle());

                return true;
            }
        }
        else if (enemyToFinisher)
        {
            enemyToFinisher->GetMesh()->SetScalarParameterValueOnMaterials(FName(TEXT("Focus")), 0);
            enemyToFinisher = nullptr;
        }
    }

    return false;
}

bool AHIWerewolf::JumpToClimb()
{
    forwardVector = cineCamera->GetForwardVector();
    startRay = cineCamera->GetComponentLocation() + forwardVector * springArm->TargetArmLength;
    float distanceToClimb = (HIIsOnEdge()) ? distanceToWallToClimbFromBuilding : distanceToWallToClimbFromFloor;
    endRay = (startRay + (forwardVector * distanceToClimb));

    // Check building where the werewolf is looking
    if (UHIGameData::HIGetDebugMode())
    {
        DrawDebugLine(GetWorld(), startRay, endRay, FColor::Red, false, 0, 0, 1);
    }

    isRayHit = GetWorld()->LineTraceSingleByChannel(outHit, GetActorLocation(), endRay, GAME_TRACE_WALL, collisionParams);
    FVector center, extent;

    if (isRayHit)
    {
        outHit.GetActor()->GetActorBounds(true, center, extent);
    }

    // If we are looking down and (the camera ray doesn't hit, or hit with vertical plane, or the wall is below the werewolf), check building at the same level
    if (endRay.Z <= startRay.Z && (!isRayHit || FVector::DotProduct(FVector(0, 0, 1), outHit.Normal) == 1 || (center.Z + extent.Z) < startRay.Z))
    {
        endRay.Z = startRay.Z;
        forwardVector = endRay - startRay;
        forwardVector.Normalize();
        endRay = startRay + forwardVector * distanceToClimb;
        isRayHit = GetWorld()->LineTraceSingleByChannel(outHit, startRay, endRay, GAME_TRACE_WALL, collisionParams);

        if (UHIGameData::HIGetDebugMode())
        {
            DrawDebugLine(GetWorld(), startRay, endRay, FColor::Black, false, 0, 0, 1);
        }
    }

    // If hit and we're not jumping or falling
    if (isRayHit && outHit.bBlockingHit && GetVelocity().Z == 0 && !isClimbing)
    {
        targetWall = Cast<AHIWall>(outHit.GetActor());

        if (targetWall && targetWall->isClimbable)
        {
            FVector wallCenter, wallExtent;
            targetWall->GetActorBounds(true, wallCenter, wallExtent);

            FVector arrowNorm = targetWall->arrowComponent->GetForwardVector();
            arrowNorm.Normalize();

            // If the hitPoint isn't the face of the wall or the top of the wall is below the werewolf, cancel the jump
            if (!FMath::IsNearlyEqual(FVector::DotProduct(arrowNorm, outHit.Normal), 1.f, KINDA_SMALL_NUMBER) ||
                (wallCenter.Z + wallExtent.Z) < startRay.Z)
            {
                CANCEL_JUMP;

                return false;
            }

            // Set abilityData values
            FVector jumpTargetPosition = outHit.ImpactPoint;
            float maxClimbingPos = wallCenter.Z + wallExtent.Z - targetWall->climbMinDistanceFromBorders;
            float minClimbingPos = startRay.Z;
            jumpTargetPosition.Z = UKismetMathLibrary::Clamp(jumpTargetPosition.Z, minClimbingPos, maxClimbingPos);

            abilityData->jumpTargetPosition = jumpTargetPosition;
            abilityData->heightOfWallToClimb = wallCenter.Z + wallExtent.Z;
            abilityData->wallClimb = true;
            abilityData->wallPosition = targetWall->GetActorLocation();

            FVector2D outScreenPos;
            float outRotationAngle = 0.f;
            // Arrow
            if (!UHIGameData::HIIsPositionOnScreen(jumpTargetPosition, outScreenPos, outRotationAngle))
            {
                buttonHUD->SetVisibility(false);

                FVector2D widgetSize = widgetref->GetCachedGeometry().Size;
                FVector2D arrowSize = widgetref->arrow->GetCachedGeometry().Size;

                outScreenPos = outScreenPos * widgetSize;
                outScreenPos.X = FMath::Clamp(outScreenPos.X, arrowSize.X * 0.5f, widgetSize.X - arrowSize.X * 0.5f);
                outScreenPos.Y = FMath::Clamp(outScreenPos.Y, arrowSize.Y * 0.5f, widgetSize.Y - arrowSize.Y * 0.5f);

                widgetref->arrow->SetVisibility(ESlateVisibility::Visible);
                widgetref->arrow->SetRenderTranslation(outScreenPos);
                widgetref->arrow->SetRenderTransformAngle(outRotationAngle + 90.f);
            }
            else // Button
            {
                widgetref->arrow->SetVisibility(ESlateVisibility::Hidden);

                buttonHUD->Move(abilityData->jumpTargetPosition);
                buttonHUD->SetActorRotation(outHit.Normal.Rotation());
                buttonHUD->SetVisibility(true);
            }

            // Apply effect jumpEffect (GE_TagJump)
            ensure(jumpEffectRef);
            abilitySystem->ApplyGameplayEffectToSelf(jumpEffectRef, 0.f, FGameplayEffectContextHandle());

            return true;
        }
    }
    else if (targetWall) // When we stop looking at the wall
    {
        CANCEL_JUMP;

        return false;
    }

    return false;
}


bool AHIWerewolf::JumpBetweenBuildings()
{
    if (GetVelocity().Z == 0)
    {
        // Ray checks
        FHitResult anchorageHit;

        if (!HICheckRaysToJumpBetweenBuildings(anchorageHit))
        {
            return false;
        }

        // Set abilityData values
        FVector center;
        FVector extent;
        anchorageHit.GetActor()->GetActorBounds(true, center, extent);
        abilityData->jumpTargetPosition = anchorageHit.ImpactPoint;
        abilityData->jumpTargetPosition.Z = center.Z + extent.Z;
        abilityData->wallClimb = false;

        FVector2D outScreenPos;
        float outRotationAngle = 0.f;

        // Arrow
        if (!UHIGameData::HIIsPositionOnScreen(anchorageHit.ImpactPoint, outScreenPos, outRotationAngle))
        {
            buttonHUD->SetVisibility(false);

            FVector2D widgetSize = widgetref->GetCachedGeometry().Size;
            FVector2D arrowSize = widgetref->arrow->GetCachedGeometry().Size;

            outScreenPos = outScreenPos * widgetSize;
            outScreenPos.X = FMath::Clamp(outScreenPos.X, arrowSize.X * 0.5f, widgetSize.X - arrowSize.X * 0.5f);
            outScreenPos.Y = FMath::Clamp(outScreenPos.Y, arrowSize.Y * 0.5f, widgetSize.Y - arrowSize.Y * 0.5f);

            widgetref->arrow->SetVisibility(ESlateVisibility::Visible);
            widgetref->arrow->SetRenderTranslation(outScreenPos);
            widgetref->arrow->SetRenderTransformAngle(outRotationAngle + 90.f);
        }
        else // Button
        {
            widgetref->arrow->SetVisibility(ESlateVisibility::Hidden);

            // Move and rotate buttonHUD
            buttonHUD->Move(abilityData->jumpTargetPosition);
            forwardVector = cineCamera->GetForwardVector();
            forwardVector.Z = GetActorForwardVector().Z;
            buttonHUD->SetActorRotation(forwardVector.RotateAngleAxis(180.f, FVector(0.f, 0.f, 1.f)).Rotation());
            buttonHUD->SetVisibility(true);
        }

        // Apply effect jumpEffect (GE_TagJump)
        ensure(jumpEffectRef);
        abilitySystem->ApplyGameplayEffectToSelf(jumpEffectRef, 0.f, FGameplayEffectContextHandle());

        return true;
    }
    else
    {
        CANCEL_JUMP;

        return false;
    }
}

bool AHIWerewolf::SameLevelExecution()
{
    FVector executionBoxPosition = GetActorLocation() + GetActorForwardVector() * sameLevelExecutionDistance;
    TArray<FHitResult> enemyHits;

    FGameplayTagContainer tagContainer;
    tagContainer.AddTag(GET_GAMEPLAY_TAG(EXECUTION_TAG));

    if (UHIGameData::HIGetDebugMode())
    {
        DrawDebugBox(GetWorld(), executionBoxPosition, FVector(sameLevelExecutionDistance, sameLevelExecutionDistance, 100.f), GetActorRotation().Quaternion(), FColor::Magenta, false, 0.1f);
    }

    isRayHit = GetWorld()->SweepMultiByChannel(enemyHits, executionBoxPosition, executionBoxPosition + 0.01f, GetActorRotation().Quaternion(), GAME_TRACE_ENEMY, FCollisionShape::MakeBox(FVector(sameLevelExecutionDistance, sameLevelExecutionDistance, 100.f)));

    if (isRayHit)
    {
        float minDot = 0.f;

        if (enemyToFinisherSameLevel && !abilitySystem->HasAnyMatchingGameplayTags(tagContainer))
        {
            enemyToFinisherSameLevel->GetMesh()->SetScalarParameterValueOnMaterials(FName(TEXT("Focus")), 0);
            enemyToFinisherSameLevel = nullptr;
        }

        for (FHitResult enemyHit : enemyHits)
        {
            // Check if the enemy is on the screen
            if (UHIGameData::HIIsPositionOnScreen(enemyHit.GetActor()->GetActorLocation()))
            {
                // @TODO: Check difference of height and recalculate distance to the enemy
                // Now this is to allow finisher only in different heights
                AHIEnemy* enem = Cast<AHIEnemy>(enemyHit.GetActor());
                if (abs(enemyHit.GetActor()->GetActorLocation().Z - GetActorLocation().Z) < 50.f && enem->HIGetDetectionValue() <= detectionExecutionThreshold)
                {
                    // If there's another enemy to finisher, target the enemy which we are looking at
                    FVector enemyVector = enemyHit.GetActor()->GetActorLocation() - GetActorLocation();
                    enemyVector.Z = 0.f;
                    enemyVector.Normalize();

                    if (FVector::DotProduct(forwardVector, enemyVector) >= minDot)
                    {
                        minDot = FVector::DotProduct(forwardVector, enemyVector);
                        enemyToFinisherSameLevel = Cast<AHIEnemy>(enemyHit.GetActor());
                    }
                }
            }
        }

        // Activate finisher
        if (enemyToFinisherSameLevel && enemyToFinisherSameLevel->HIGetAttributes()->Gethealth() > 0)
        {
            //Boss special checks
            bool bossTagOwned = false;
            {
                CHECK_HAS_TAG(enemyToFinisherSameLevel->GetAbilitySystemComponent(), BOSS_TAG, bossTagOwned);
            }
            if (bossTagOwned)
            {
                bool bossInmunityActived = false;
                CHECK_HAS_TAG(enemyToFinisherSameLevel->GetAbilitySystemComponent(), INMUNITY_TAG, bossInmunityActived);

                if (bossInmunityActived == false)
                {
                    enemyToFinisher = nullptr;
                    return false;
                }
            }


            if (!abilitySystem->HasAnyMatchingGameplayTags(tagContainer))
            {
                enemyToFinisherSameLevel->GetMesh()->SetScalarParameterValueOnMaterials(FName(TEXT("Focus")), 1);
            }

            abilityData->finisherPosition = enemyToFinisherSameLevel->HIGetExecutionPosition(true, abilityData->backExecution);
            ensure(jumpExecutionEffectRef);
            abilitySystem->ApplyGameplayEffectToSelf(jumpExecutionEffectRef, 0.f, FGameplayEffectContextHandle());

            return true;
        }
    }
    else if (enemyToFinisherSameLevel)
    {
        enemyToFinisherSameLevel->GetMesh()->SetScalarParameterValueOnMaterials(FName(TEXT("Focus")), 0);
        enemyToFinisherSameLevel = nullptr;
    }

    return false;
}

bool AHIWerewolf::CombatFinisher()
{

    FGameplayTagContainer tagContainer;
    tagContainer.AddTag(GET_GAMEPLAY_TAG(EXECUTION_TAG));

    forwardVector = cineCamera->GetForwardVector();
    forwardVector.Z = 0.f;
    forwardVector.Normalize();
    startRay = GetActorLocation() + FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) + forwardVector * topExecutionCapsuleRadius;
    endRay = startRay + FVector(0.f, 0.f, -topExecutionCapsuleHeight);
    TArray<FHitResult> enemyHits;
    FCollisionQueryParams queryParams;
    queryParams.AddIgnoredActor(this);
    isRayHit = GetWorld()->SweepMultiByChannel(enemyHits, startRay, endRay, FQuat::Identity, GAME_TRACE_ENEMY, FCollisionShape::MakeCapsule(topExecutionCapsuleRadius, topExecutionCapsuleHeight / 2), queryParams);



    if (isRayHit)
    {
        float minDot = 0.f;

        if (enemyToCombatFinisher && !abilitySystem->HasAnyMatchingGameplayTags(tagContainer))
        {
            enemyToCombatFinisher->GetMesh()->SetScalarParameterValueOnMaterials(FName(TEXT("Focus")), 0);
            enemyToCombatFinisher = nullptr;
        }

        for (FHitResult enemyHit : enemyHits)
        {
            // Check if the enemy is on the screen
            if (UHIGameData::HIIsPositionOnScreen(enemyHit.GetActor()->GetActorLocation()))
            {

                // If there's another enemy to finisher, target the enemy which we are looking at
                FVector enemyVector = enemyHit.GetActor()->GetActorLocation() - GetActorLocation();
                enemyVector.Z = 0.f;
                enemyVector.Normalize();

                if (FVector::DotProduct(forwardVector, enemyVector) >= minDot)
                {
                    minDot = FVector::DotProduct(forwardVector, enemyVector);
                    enemyToCombatFinisher = Cast<AHIEnemy>(enemyHit.GetActor());
                }
            }
        }

        // Activate finisher
        if (enemyToCombatFinisher && enemyToCombatFinisher->HIGetAttributes()->Gethealth() > 0)
        {
            if (enemyToCombatFinisher->HIGetFear() >= enemyToCombatFinisher->HIGetMaxFear())
            {



                if (!abilitySystem->HasAnyMatchingGameplayTags(tagContainer))
                {
                    enemyToCombatFinisher->GetMesh()->SetScalarParameterValueOnMaterials(FName(TEXT("Focus")), 1);
                }

                abilityData->finisherPosition = enemyToCombatFinisher->GetActorLocation() - enemyToCombatFinisher->GetActorForwardVector() * 50.f;
                ensure(jumpFinisherEffectRef);
                abilitySystem->ApplyGameplayEffectToSelf(jumpFinisherEffectRef, 0.f, FGameplayEffectContextHandle());

                return true;
            }
        }
    }
    else if (enemyToCombatFinisher)
    {
        enemyToCombatFinisher->GetMesh()->SetScalarParameterValueOnMaterials(FName(TEXT("Focus")), 0);
        enemyToCombatFinisher = nullptr;
    }

    return false;
}

void AHIWerewolf::SetInitialValues()
{
    physicAnimComponent->SetSkeletalMeshComponent(GetMesh());

    if (statsDataTable)
    {
        FString ContextString = TEXT("Data table context");
        FHI_WerewolfDatatable* Row = statsDataTable->FindRow<FHI_WerewolfDatatable>(FName(TEXT("Werewolf")), ContextString, true);

        if (Row)
        {
            distanceToWallToClimbFromFloor = Row->distanceToWallToClimbFromFloor;
            distanceToWallToClimbFromBuilding = Row->distanceToWallToClimbFromBuilding;
            climbingSpeed = Row->climbingSpeed;
            distanceToBordersToJump = Row->distanceToBordersToJump;
            distanceToBuildingToJump = Row->distanceToBuildingToJump;
            anglesToBuildingToJump = Row->anglesToBuildingToJump;
            healingTick = Row->healingPerSeconds;
            startHealingHP = Row->startHealingHP;

            if (anglesToBuildingToJump.Num() == 0)
            {
                anglesToBuildingToJump.Add(10.f);
            }

            topExecutionCapsuleRadius = Row->capsuleRadius;
            topExecutionCapsuleHeight = Row->capsuleHeight;
            sameLevelExecutionDistance = Row->sameLevelExecutionDistance;
            detectionExecutionThreshold = Row->finisherThreshold;
        }
    }

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    if (abilitySystem && abilityDataTable)
    {
        attributes = Cast<UHIWerewolfAttributes>(abilitySystem->InitStats(UHIWerewolfAttributes::StaticClass(), abilityDataTable));
        HIActivateDelegates();

        for (size_t i = 0; i < abiliyList.Num(); ++i)
        {
            abilitySystem->GiveAbility(FGameplayAbilitySpec(abiliyList[i].GetDefaultObject(), 1, 0));
        }

        comboSystem->HIAttachAbilitySystem(abilitySystem);
        HIInitializeAbilities();
        GetCharacterMovement()->MaxWalkSpeed = attributes->Getspeed();

        if (WidgetClass)
        {
            widgetref = CreateWidget<UHIVincentHUD>(GetWorld(), WidgetClass);
            widgetref->AddToViewport();
            widgetref->HIInitVariables(attributes);
            widgetref->HISetMaxRage(HIGetMaxRage());
        }

    }

    buttonHUD = GetWorld()->SpawnActor<AHIButtonHUD>(buttonBP);
    ensure(buttonHUD);

#if CHEATS
    AHITeleportPawn* teleportPawn = GetWorld()->SpawnActor<AHITeleportPawn>(AHITeleportPawn::StaticClass());
    if (teleportPawn)
    {
        UHIGameData::HISetTeleportPawn(teleportPawn);
    }
#endif

    camManager = Cast<AHICameraManager>(GetWorld()->GetFirstPlayerController()->PlayerCameraManager);

    abilityData = NewObject<UHIAbilityData>();
}

void AHIWerewolf::SetGameplayEffectsReferences()
{
    ensure(jumpEffect);
    jumpEffectRef = Cast<UGameplayEffect>(jumpEffect->GetDefaultObject());

    ensure(climbEffect);
    climbEffectRef = Cast<UGameplayEffect>(climbEffect->GetDefaultObject());

    ensure(jumpExecutionEffect);
    jumpExecutionEffectRef = Cast<UGameplayEffect>(jumpExecutionEffect->GetDefaultObject());

    ensure(jumpFinisherEffect);
    jumpFinisherEffectRef = Cast<UGameplayEffect>(jumpFinisherEffect->GetDefaultObject());

    ensure(stopMovingEffect);
    stopMovingEffectRef = Cast<UGameplayEffect>(stopMovingEffect->GetDefaultObject());

    RegenerationEffectRef = NewObject<UGameplayEffect>();
}

void AHIWerewolf::ThrowEnemy(AHIEnemy* _enemy)
{
    if (enemygrabbed)
    {
        enemygrabbed->DetachRootComponentFromParent();
        enemygrabbed = nullptr;
    }

    _enemy->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("RightHandSocket"));
    enemygrabbed = _enemy;

    //Launch Throw enemy GAS ability
    FGameplayEventData DataEvent;
    FGameplayTag launchTag = GET_GAMEPLAY_TAG(THROW_ENEMY_TAG);
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, launchTag, DataEvent);
}

bool AHIWerewolf::DetachEnemy(AHIEnemy* _enemy)
{
    FRotator changeRot;
    AHIEnemy* closestVictim = nullptr;

    APlayerController* Controll = GetController<APlayerController>();

    TArray<FHitResult> hitResults;

    TArray<AActor*> HitActors;
    GetWorld()->SweepMultiByChannel(hitResults, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(2500));

    for (FHitResult Iter : hitResults)
    {
        HitActors.Add(Iter.GetActor());
    }

    float num = HitActors.Num();

    if (num > 0)
    {
        float dis = 0;
        float mindis = 0;
        AActor* closest = nullptr;

        for (int i = 0; i < num; ++i)
        {
            if (HitActors[i] != _enemy)
            {
                dis = (GetActorLocation() - HitActors[i]->GetActorLocation()).Size();

                if (mindis == 0 || dis < mindis)
                {
                    if (UHIGameData::HIIsPositionOnScreen(hitResults[i].GetActor()->GetActorLocation()))
                    {
                        if (FMath::Abs(GetActorLocation().Z - HitActors[i]->GetActorLocation().Z) < 50.f)
                        {
                            closest = HitActors[i];
                            mindis = dis;
                        }
                    }
                }
            }

        }

        if (closest)
        {
            closestVictim = Cast<AHIEnemy>(closest);
        }
    }

    _enemy->DetachRootComponentFromParent();
    GetCapsuleComponent()->SetWorldRotation(FRotator(0.f, 0.f, 0.f));

    if (closestVictim)
    {
        closestVictim->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(stopMovingEffectRef, 0.f, FGameplayEffectContextHandle());

        changeRot = (closestVictim->GetActorLocation() - GetActorLocation()).ToOrientationRotator();
        SetActorRotation(changeRot);

        _enemy->GetMesh()->SetAllBodiesBelowSimulatePhysics("Hips", true, false);
        _enemy->enemyToHit = closestVictim;

        FRotator lookingEnemyRotation = GetActorRotation();

        FVector distToClosesstVictim = (closestVictim->GetActorLocation() - GetActorLocation()).GetSafeNormal(0.f);
        float dotProduct = FVector::DotProduct(GetActorForwardVector(), distToClosesstVictim);
        float angleToConeDirection = FMath::RadiansToDegrees(FMath::Acos(dotProduct));
        lookingEnemyRotation.Yaw -= angleToConeDirection;
        lookingEnemyRotation.Normalize();

        SetActorRotation(lookingEnemyRotation);

        closestVictim = nullptr;

        return true;
    }
    else
    {
        _enemy->GetMesh()->SetSimulatePhysics(true);
        FVector launch = (_enemy->GetActorLocation() - GetActorLocation());
        launch.Normalize();
        _enemy->GetMesh()->AddImpulse(launch * 2500.f);
        return false;
    }
}

void AHIWerewolf::HIActivateDelegates()
{
    maxHealthChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(attributes->GetmaxHealthAttribute()).AddUObject(this, &AHIWerewolf::HIMaxHealthChanged);
    healthChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(attributes->GethealthAttribute()).AddUObject(this, &AHIWerewolf::HIHealthChanged);
    rageChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(attributes->GetchargedValueAttribute()).AddUObject(this, &AHIWerewolf::HIRageChanged);
    howlChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(attributes->GethowlAttribute()).AddUObject(this, &AHIWerewolf::HIHowlChanged);
    speedChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(attributes->GetspeedAttribute()).AddUObject(this, &AHIWerewolf::HIspeedChanged);
}

bool AHIWerewolf::HICheckRaysToJumpBetweenBuildings(FHitResult& anchorageHit_)
{
    if (!HIIsOnEdge())
    {
        return false;
    }

    // 1. If we are on the edge of the building
    forwardVector = cineCamera->GetForwardVector();
    forwardVector.Z = 0.f;
    forwardVector.Normalize();
    FRotator forwardRotator;
    FHitResult buildingHit;

    for (float angleToJump : anglesToBuildingToJump)
    {
        forwardRotator = forwardVector.Rotation();
        forwardRotator.Pitch -= angleToJump;
        startRay = GetActorLocation() + FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) + forwardVector * distanceToBordersToJump;
        endRay = startRay + forwardRotator.Vector() * distanceToBuildingToJump;

        if (UHIGameData::HIGetDebugMode())
        {
            DrawDebugLine(GetWorld(), startRay, endRay, FColor::Magenta, false, 0, 0, 1);
        }

        isRayHit = GetWorld()->LineTraceSingleByChannel(anchorageHit_, startRay, endRay, GAME_TRACE_ANCHORAGE, collisionParams);

        AHIAnchorage* pAnchorage = Cast<AHIAnchorage>(anchorageHit_.GetActor());

        if (pAnchorage && isRayHit)
        {
            endRay = startRay + forwardRotator.Vector() * distanceToBuildingToJump;
            isRayHit = GetWorld()->LineTraceSingleByChannel(buildingHit, startRay, endRay, GAME_TRACE_BUILDING, collisionParams); // Si est� pegado a la pared del edificio no lo atraviesa

            if (isRayHit)
            {
                if (FVector::DistSquared(anchorageHit_.ImpactPoint, startRay) > FVector::DistSquared(buildingHit.ImpactPoint, startRay))
                {
                    return false;
                }
            }

            return true;
        }
    }

    return false;
}

bool AHIWerewolf::HIIsOnEdge()
{
    // Ray from 'in front of the camera (in the horizontal plane with the werewolf's head)' to 'down'
    FVector forwardVectorBuilding = cineCamera->GetForwardVector();
    forwardVectorBuilding.Z = 0.f;
    forwardVectorBuilding.Normalize();
    FVector startRayBuilding = GetActorLocation() + FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) + forwardVectorBuilding * distanceToBordersToJump;
    FVector endRayBuilding = startRayBuilding + FVector(0.f, 0.f, -(GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2) - 50.f); // Height of the werewolf capsule - 50.f

    if (UHIGameData::HIGetDebugMode())
    {
        DrawDebugLine(GetWorld(), startRayBuilding, endRayBuilding, FColor::Red, false, 0, 0, 1);
    }

    FHitResult outHitBuilding;
    bool isRayHitBuilding = GetWorld()->LineTraceSingleByChannel(outHitBuilding, startRayBuilding, endRayBuilding, ECC_Camera, collisionParams);

    if (UHIGameData::HIGetDebugMode() && isRayHitBuilding)
    {
        DrawDebugLine(GetWorld(), startRayBuilding, endRayBuilding, FColor::Green, false, 0, 0, 1);
    }

    return !isRayHitBuilding;
}

void AHIWerewolf::SetIsClimbing(bool _isClimbing)
{
    isClimbing = _isClimbing;
}

void AHIWerewolf::SetIsDoingFinisher(bool _isDoingFinisher)
{
    isDoingFinisher = _isDoingFinisher;
}

void AHIWerewolf::OnHitBegin(AActor* _selfActor, AActor* _otherActor, FVector _normalImpulse, const FHitResult& _hit)
{
//     if (isClimbing)
//     {
//         AHIWall* wall = Cast<AHIWall>(_otherActor);
// 
//         if (wall)
//         {
//             // Raycast to see if the wall is in front of the werewolf
//             FHitResult hitResult;
// 
//             //(_otherActor->GetActorLocation()-_selfActor->GetActorLocation()) *500.f
//             bool traceResult = GetWorld()->LineTraceSingleByChannel(hitResult, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 500.f, GAME_TRACE_BUILDING, collisionParams);
//             FVector safeDirection = hitResult.Normal * -1;
// 
//             if (traceResult && hitResult.bBlockingHit)
//             {
//                 GetCharacterMovement()->GravityScale = 0.f;
//                 //SetActorRotation(safeDirection.Rotation());
//             }
//         }
//     }
}

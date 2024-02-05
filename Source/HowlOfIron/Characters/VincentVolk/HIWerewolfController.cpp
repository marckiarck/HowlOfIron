// @AUTHORS: Marco Fern�ndez, Guillermo Su�rez


#include "HIWerewolfController.h"
#include "HIWerewolf.h"
#include "Game/HIGameData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "HIMacros.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Menus/HIPauseMenu.h"
#include "UI/Menus/HIMainMenu.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Game/HIGameInstance.h"
#include "Components/TextBlock.h"
#include "MapLogic/HITeleportPawn.h"

FVector FixMovement(FVector Forward)
{
    auto Result = FVector(Forward.X, Forward.Y, 0.f);
    Result.Normalize();
    return Result;
}


AHIWerewolfController::AHIWerewolfController() : ownFPS(0.f)
{

}

AHIWerewolfController::~AHIWerewolfController()
{
    UE_LOG(LogTemp, Display, TEXT("HIWerewolfController destructor called"));
}

void AHIWerewolfController::BeginPlay()
{
    Super::BeginPlay();

    werewolfOwner = UHIGameData::HIGetPlayerWerewolf();

    if (!gameInstance)
    {
        gameInstance = Cast<UHIGameInstance>(GetGameInstance());
    }

    UHIGameData::HISetPlayerController(this);

    // Movement
    InputComponent->BindAxis("MoveForward", this, &AHIWerewolfController::HIMoveForward).bConsumeInput = false;
    InputComponent->BindAxis("MoveSide", this, &AHIWerewolfController::HIMoveSide);
    InputComponent->BindAction("Jump", IE_Pressed, this, &AHIWerewolfController::HIJump);

    // Camera
    InputComponent->BindAxis("CameraX", this, &AHIWerewolfController::HICameraX);
    InputComponent->BindAxis("CameraY", this, &AHIWerewolfController::HICameraY);
    camMana = Cast<AHICameraManager>(PlayerCameraManager);

    // Combat actions
    InputComponent->BindAction("Howl", IE_Pressed, this, &AHIWerewolfController::HIHowl);
    InputComponent->BindAction("Dash", IE_Pressed, this, &AHIWerewolfController::HIDash);
    InputComponent->BindAction("LightAttack", IE_Pressed, this, &AHIWerewolfController::HILightAttack);
    InputComponent->BindAction("HeavyAttack", IE_Pressed, this, &AHIWerewolfController::HIHeavyAttack);
    InputComponent->BindAction("Finisher", IE_Pressed, this, &AHIWerewolfController::HIFinisher);
    InputComponent->BindAction("Target", IE_Pressed, this, &AHIWerewolfController::HITarget);

    // Game actions
    InputComponent->BindAction("DebugMode", IE_Pressed, this, &AHIWerewolfController::HIDebugMode);
    // InputComponent->BindAction("ResetLevel", IE_Pressed, this, &AHIWerewolfController::HIResetLevel);

    // Teleport cheat
    InputComponent->BindAction("TeleportCheat", IE_Pressed, this, &AHIWerewolfController::HITeleportCheat);
    InputComponent->BindAxis("TeleportDown", this, &AHIWerewolfController::HITeleportDown);
    InputComponent->BindAxis("TeleportUp", this, &AHIWerewolfController::HITeleportUp);

    FInputActionBinding& escape = InputComponent->BindAction("PauseMenu", IE_Pressed, this, &AHIWerewolfController::HIPauseMenuAction);
    escape.bExecuteWhenPaused = true; // When game is paused catch this event

    // @TODO: A lo mejor falta released

    // Init Pause Menu
    if (pauseMenuRef)
    {
        pauseMenu = CreateWidget<UHIPauseMenu>(this, pauseMenuRef);

        if (pauseMenu)
        {
            pauseMenu->AddToViewport(2);
            // Pause Menu isn't visible by default
            pauseMenu->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

    tooltipWidget = CreateWidget<UHITooltipWidget>(this, TooltipWidgetClass);
    tooltipWidget->AddToViewport();
    tooltipWidget->SetVisibility(ESlateVisibility::Collapsed);
    UHIGameData::HIGetGameInstance()->tooltipWidget = tooltipWidget;
}

void AHIWerewolfController::Tick(float _deltaSeconds)
{
    Super::Tick(_deltaSeconds);

    if (werewolfOwner && werewolfOwner->widgetref)
    {
        if (pauseMenu->HIGetFPSIndex() == 1)
        {
            HICalculateFPS(1.0f / _deltaSeconds);
            werewolfOwner->widgetref->HIUpdateFPSMessage(HIGetFPS());
        }
    }
}

void AHIWerewolfController::HIMoveForward(float _value)
{
#if CHEATS
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        if (FMath::Abs(_value) > 0.25f)
        {
            const FRotator rot = GetControlRotation();
            const FRotator yaw(0, rot.Yaw, 0);
            const FVector dir = FRotationMatrix(yaw).GetUnitAxis(EAxis::X);
            teleportPawn->AddMovementInput(FixMovement(dir), _value);
        }
        return;
    }
#endif

    werewolfOwner->forwardVectorInput = FVector::ZeroVector;
    if (_value != 0 && FMath::Abs(_value) > 0.25f)
    {
        UAbilitySystemComponent* ownerAbilitySystem = werewolfOwner->GetAbilitySystemComponent();
        FGameplayTagContainer tagContainer;
        ownerAbilitySystem->GetOwnedGameplayTags(tagContainer);

        //owner->AddMovementInput(FixMovement(owner->GetActorForwardVector()), _value);

        const FRotator Rotation = GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        werewolfOwner->forwardVectorInput = FixMovement(Direction) * _value;

        movementImput.X = _value;

        if (tagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName(MOVE_DISABLED_TAG))) == false)
        {
            if (werewolfOwner->GetCharacterMovement()->MaxWalkSpeed != 0.f)
            {
                werewolfOwner->AddMovementInput(FixMovement(Direction), _value);
            }
        }
    }
    else
    {
        movementImput.X = 0;
    }
}

void AHIWerewolfController::HIMoveSide(float _value)
{
#if CHEATS
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        if (FMath::Abs(_value) > 0.25f)
        {
            const FRotator rot = GetControlRotation();
            const FRotator yaw(0, rot.Yaw, 0);
            const FVector dir = FRotationMatrix(yaw).GetUnitAxis(EAxis::Y);
            teleportPawn->AddMovementInput(FixMovement(dir), _value);
        }
        return;
    }
#endif

    werewolfOwner->sideVectorInput = FVector::ZeroVector;
    if (_value != 0 && FMath::Abs(_value) > 0.25f)
    {
        UAbilitySystemComponent* ownerAbilitySystem = werewolfOwner->GetAbilitySystemComponent();
        FGameplayTagContainer tagContainer;
        ownerAbilitySystem->GetOwnedGameplayTags(tagContainer);

        const FRotator Rotation = GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        werewolfOwner->sideVectorInput = FixMovement(Direction) * _value;

        movementImput.Y = _value;

        // add movement in that direction
        if (tagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName(MOVE_DISABLED_TAG))) == false)
        {
            if (werewolfOwner->GetCharacterMovement()->MaxWalkSpeed != 0.f)
            {
                werewolfOwner->AddMovementInput(FixMovement(Direction), _value);

                if (camMana->currentCamView == CameraView::HUNT)
                {
                    if (_value < 0)
                    {
                        if (camDeviation < 100)
                        {
                            camDeviation++;
                            werewolfOwner->springArm->SocketOffset.Y = camMana->leftDeviation - camDeviation;
                        }
                    }
                    else if (_value > 0)
                    {
                        if (camDeviation > 0)
                        {
                            camDeviation -= 0.5f;
                            werewolfOwner->springArm->SocketOffset.Y = camMana->leftDeviation - camDeviation;
                        }

                    }
                }
                else
                {
                    if (camDeviation > 0)
                    {
                        camDeviation -= 0.5f;
                        werewolfOwner->springArm->SocketOffset.Y = camMana->leftDeviation - camDeviation;
                    }
                }
            }
        }
    }
    else
    {
        movementImput.Y = 0;

        if (camDeviation > 0)
        {
            camDeviation -= 0.5f;
            werewolfOwner->springArm->SocketOffset.Y = camMana->leftDeviation - camDeviation;
        }
    }
}

void AHIWerewolfController::HICameraX(float _value)
{
#if CHEATS
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        if (FMath::Abs(_value) > 0.25f)
        {
            teleportPawn->AddControllerYawInput(_value * GetWorld()->GetDeltaSeconds() * gameInstance->mouseSensivility * gameInstance->reverseYCamera);
        }
        return;
    }
#endif

    UAbilitySystemComponent* ownerAbilitySystem = werewolfOwner->GetAbilitySystemComponent();
    FGameplayTagContainer tagContainer;

    ownerAbilitySystem->GetOwnedGameplayTags(tagContainer);

    if (camMana->targetedActor)
    {
        if (_value < -0.75f)
        {
            camMana->TargetChange(true);
        }

        if (_value > 0.75f)
        {
            camMana->TargetChange(false);
        }
    }
    else
    {
        if (_value != 0 && FMath::Abs(_value) > 0.25f && tagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName(CAMERA_MOVE_DISABLED_TAG))) == false)
        {
            werewolfOwner->AddControllerYawInput(_value * GetWorld()->GetDeltaSeconds() * gameInstance->mouseSensivility * gameInstance->reverseYCamera);
        }
    }
}

void AHIWerewolfController::HICameraY(float _value)
{
#if CHEATS
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        if (FMath::Abs(_value) > 0.25f)
        {
            teleportPawn->AddControllerPitchInput(-_value * GetWorld()->GetDeltaSeconds() * gameInstance->mouseSensivility * gameInstance->reverseXCamera);
        }
        return;
    }
#endif

    UAbilitySystemComponent* ownerAbilitySystem = werewolfOwner->GetAbilitySystemComponent();
    FGameplayTagContainer tagContainer;

    ownerAbilitySystem->GetOwnedGameplayTags(tagContainer);

    if (_value != 0 && FMath::Abs(_value) > 0.25f && tagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName(CAMERA_MOVE_DISABLED_TAG))) == false)
    {
        werewolfOwner->AddControllerPitchInput(-_value * GetWorld()->GetDeltaSeconds() * gameInstance->mouseSensivility * gameInstance->reverseXCamera);
    }
}

void AHIWerewolfController::HIJump()
{
#if CHEATS
    // If teleportPawn->return to avoid errors
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        return;
    }
#endif

    UAbilitySystemComponent* ownerAbilitySystem = werewolfOwner->GetAbilitySystemComponent();
    FGameplayTagContainer tagContainer;

    ownerAbilitySystem->GetOwnedGameplayTags(tagContainer);

    if (tagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName(MOVE_DISABLED_TAG))) == false)
    {
        werewolfOwner->HIActivateJump();
    }
}

void AHIWerewolfController::HIHowl()
{
#if CHEATS
    // If teleportPawn->return to avoid errors
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        return;
    }
#endif

    UAbilitySystemComponent* ownerAbilitySystem = werewolfOwner->GetAbilitySystemComponent();
    FGameplayTagContainer tagContainer;

    ownerAbilitySystem->GetOwnedGameplayTags(tagContainer);

    if (tagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName(MOVE_DISABLED_TAG))) == false)
    {
        werewolfOwner->HIActivateHowl();
    }
}

void AHIWerewolfController::HIFinisher()
{
#if CHEATS
    // If teleportPawn->return to avoid errors
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        return;
    }
#endif

    UAbilitySystemComponent* ownerAbilitySystem = werewolfOwner->GetAbilitySystemComponent();
    FGameplayTagContainer tagContainer;

    ownerAbilitySystem->GetOwnedGameplayTags(tagContainer);

    if (tagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName(MOVE_DISABLED_TAG))) == false)
    {
        werewolfOwner->HIActivateFinisher();
    }
}

void AHIWerewolfController::HITarget()
{
#if CHEATS
    // If teleportPawn->return to avoid errors
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        return;
    }
#endif

    UAbilitySystemComponent* ownerAbilitySystem = werewolfOwner->GetAbilitySystemComponent();
    FGameplayTagContainer tagContainer;

    ownerAbilitySystem->GetOwnedGameplayTags(tagContainer);

    if (tagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName(MOVE_DISABLED_TAG))) == false)
    {
        if (camMana->targetedActor)
        {
            if (camMana->targetedActor->targetEnemyReference)
            {
                camMana->targetedActor->targetEnemyReference->HISetTargetImageVisibility(ESlateVisibility::Collapsed);
            }
            camMana->TargetEmpty();
        }
        else
        {
            camMana->TargetDetection();
        }
    }
}

void AHIWerewolfController::HIDebugMode()
{
    UHIGameData::HIDebugModeToggle();
}

void AHIWerewolfController::HIResetLevel()
{
#if WITH_EDITOR
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
    UHIGameData::HIClearStaticReferences();
#endif
}

void AHIWerewolfController::HITeleportCheat()
{
#if CHEATS
    AHIWerewolf* werewolf = UHIGameData::HIGetPlayerWerewolf();
    AHITeleportPawn* teleportPawn = UHIGameData::HIGetTeleportPawn();

    if (werewolf && teleportPawn)
    {
        AHITeleportPawn* actualTeleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
        if (actualTeleportPawn) // Teleport the werewolf to teleportPawn position
        {
            werewolf->SetActorTransform(teleportPawn->GetActorTransform());
            GetWorld()->GetFirstPlayerController()->Possess(werewolf);
        }
        else // Possess teleportPawn
        {
            teleportPawn->SetActorTransform(werewolf->GetActorTransform());
            GetWorld()->GetFirstPlayerController()->Possess(teleportPawn);
        }
    }
#endif
}

void AHIWerewolfController::HITeleportDown(float _value)
{
#if CHEATS
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        if (FMath::Abs(_value) > 0.25f)
        {
            teleportPawn->AddMovementInput(teleportPawn->GetActorUpVector(), -_value);
        }
    }
#endif
}

void AHIWerewolfController::HITeleportUp(float _value)
{
#if CHEATS
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        if (FMath::Abs(_value) > 0.25f)
        {
            teleportPawn->AddMovementInput(teleportPawn->GetActorUpVector(), _value);
        }
    }
#endif
}

void AHIWerewolfController::HICalculateFPS(float _deltaTime)
{
    ownFPS = _deltaTime;
}

float AHIWerewolfController::HIGetFPS()
{
    return ownFPS;
}

AHIWerewolf* AHIWerewolfController::HIGetWerewolf()
{
    return werewolfOwner;
}

void AHIWerewolfController::HIPauseMenuAction()
{
    if (pauseMenu)
    {
        if (pauseMenu->GetVisibility() == ESlateVisibility::Collapsed)
        {
            // Set Pause Menu Visible
            pauseMenu->HIInitVincentHUD();
            pauseMenu->SetVisibility(ESlateVisibility::Visible);
            UWidgetBlueprintLibrary::SetInputMode_UIOnly(this, pauseMenu);
            UGameplayStatics::SetGamePaused(GetWorld(), true);
            werewolfOwner->widgetref->SetVisibility(ESlateVisibility::Collapsed);
            bShowMouseCursor = true;
        }
    }
}

void AHIWerewolfController::HIDash()
{
#if CHEATS
    // If teleportPawn->return to avoid errors
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        return;
    }
#endif

    UAbilitySystemComponent* ownerAbilitySystem = werewolfOwner->GetAbilitySystemComponent();
    FGameplayTagContainer tagContainer;

    ownerAbilitySystem->GetOwnedGameplayTags(tagContainer);

    if (tagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName(MOVE_DISABLED_TAG))) == false)
    {
        werewolfOwner->HIActivateDash();
    }
}

void AHIWerewolfController::HILightAttack()
{
#if CHEATS
    // If teleportPawn->return to avoid errors
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        return;
    }
#endif

    UAbilitySystemComponent* ownerAbilitySystem = werewolfOwner->GetAbilitySystemComponent();
    FGameplayTagContainer tagContainer;

    ownerAbilitySystem->GetOwnedGameplayTags(tagContainer);

    if (tagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName(MOVE_DISABLED_TAG))) == false)
    {
        werewolfOwner->HIActivateLightAttack();
    }
}

void AHIWerewolfController::HIHeavyAttack()
{
#if CHEATS
    // If teleportPawn->return to avoid errors
    AHITeleportPawn* teleportPawn = GetWorld()->GetFirstPlayerController()->GetPawn<AHITeleportPawn>();
    if (teleportPawn)
    {
        return;
    }
#endif

    UAbilitySystemComponent* ownerAbilitySystem = werewolfOwner->GetAbilitySystemComponent();
    FGameplayTagContainer tagContainer;

    ownerAbilitySystem->GetOwnedGameplayTags(tagContainer);

    if (tagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName(MOVE_DISABLED_TAG))) == false)
    {
        werewolfOwner->HIActivateHeavyAttack();
    }
}

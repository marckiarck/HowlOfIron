// @AUTHORS: Pablo, Guillermo Su�rez, Carlos Fernandez

#include "HIEnemy.h"
#include "IA/HIMasterSecurity.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "MapLogic/HIGameOverworldDirector.h"
#include "IA/HIPatrol.h"
#include "Game/HIGameInstance.h"
#include "Game/HICameraManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UI/HIEnemyHUD.h"
#include "GAS/Structs/HIFGameplayEventData.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "IA/HIMasterSecurity.h"
#include "HIAlarm.h"
#include "HIMacros.h"
#include "HI_DT_Enemy.h"
#include "Game/HIGameData.h"
#include "HI_DT_EnemyAccessory.h"
#include "BrainComponent.h"
#include <DrawDebugHelpers.h>

AHIEnemy::AHIEnemy() :
	actualWeapon(nullptr),
	previousWeapon(nullptr),
	playerLastSeen(false)
{
	PrimaryActorTick.bCanEverTick = true;

	shoutAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ShoutAudioComponent"));
	shoutAudioComponent->SetupAttachment(RootComponent);

	physicAnimComponent = CreateDefaultSubobject<UPhysicalAnimationComponent>(TEXT("PhysicalAnimationComponent"));

	enemyBars = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	enemyBars->SetupAttachment(RootComponent);

	enemyTargetImage = CreateDefaultSubobject<UWidgetComponent>(TEXT("TargetImage"));
	enemyTargetImage->SetupAttachment(RootComponent);

	enemiesAttributes = CreateDefaultSubobject<UHIEnemiesAttributes>(TEXT("Attributes"));
	detectorComponent = CreateDefaultSubobject<UHIDetectorActorComponent>(TEXT("DetectorActorComponent"));

	executionSameLevelPoint = CreateDefaultSubobject<UHIExecutionPointComponent>(TEXT("SameLevelExecutionPoint"));
	executionTopLevelPoint = CreateDefaultSubobject<UHIExecutionPointComponent>(TEXT("TopLevelExecutionPoint"));
}


AHIEnemy::~AHIEnemy()
{
	UE_LOG(LogTemp, Log, TEXT("Enemy script deleted."));
	UHIGameData::HIRemoveEnemyFromArray(this);

}

void AHIEnemy::BeginPlay()
{
	Super::BeginPlay();

	physicAnimComponent->SetSkeletalMeshComponent(GetMesh());

	if (abilitySystem && statsDatatable && enemiesAttributes)
	{
		const UAttributeSet* attributeinit = abilitySystem->InitStats(UHIEnemiesAttributes::StaticClass(), statsDatatable);
		enemiesAttributes = Cast<UHIEnemiesAttributes>(attributeinit);
		GetCharacterMovement()->MaxWalkSpeed = enemiesAttributes->Getspeed();

		detectorComponent->HIAttachAbilitySystem(abilitySystem);
		detectorComponent->HIInitializeDetectionValue(statsDatatable);

		HIActivateDelegates();

		for (size_t i = 0; i < abiliyList.Num(); ++i)
		{
			FGameplayAbilitySpecHandle specHandle = abilitySystem->GiveAbility(FGameplayAbilitySpec(abiliyList[i].GetDefaultObject(), 1, 0));
		}

		if (!tagtoAddOnStart.Num() == 0)
		{
			abilitySystem->AddLooseGameplayTags(tagtoAddOnStart);
		}
		if (tagClass.IsValid())
		{
			abilitySystem->AddLooseGameplayTag(tagClass);
		}

		HIAssignCharacterType();


	}

	if (enemyBars)
	{
		hudReference = Cast<UHIEnemyHUD>(enemyBars->GetUserWidgetObject());
		if (hudReference)
		{
			hudReference->HIInitAttributes(enemiesAttributes);
			hudReference->HIChangeMaxFear(HIGetMaxFear());
			hudReference->HIChangeMaxDetection(enemiesAttributes->GetmaxDetectionMeter());
		}
	}

	if (enemyTargetImage)
	{
		targetEnemyReference = Cast<UHITargetEnemyHUD>(enemyTargetImage->GetUserWidgetObject());

		if (targetEnemyReference)
		{
			targetEnemyReference->HISetTargetImageVisibility(ESlateVisibility::Collapsed);
			// HISetTargetHUDVisibility(ESlateVisibility::Collapsed);
		}
	}

	dynamicMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this, FName(TEXT("dynamicMaterial")));
	GetMesh()->SetMaterial(0, dynamicMaterial);

	if (datatable)
	{
		FString ContextString = TEXT("Data table context");
		FHI_DT_Enemy* Row = nullptr;
		TArray<FName> RowNames = datatable->GetRowNames();

		Row = datatable->FindRow<FHI_DT_Enemy>(RowNames[dataTableRow], ContextString, true);
		detectorComponent->HISetDetectionLostValue(Row->decreaseDetectionPerSecond);
		launchGrenadeRadious = Row->launchGrenadeRadious;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No Datatable Mutton."));
	}

	// Load accessories
	if (accessoriesDataTable)
	{
		FString ContextString = TEXT("Data table context");
		FHI_DT_EnemyAccessory* Row = nullptr;
		TArray<FName> RowNames = accessoriesDataTable->GetRowNames();

		bool hasWeapon = false;
		//for (FName accessoryName : accessoriesNames)
		for (FHIEnemyAccessoryStruct accessoryStruct : accessoriesStructs)
		{
			Row = accessoriesDataTable->FindRow<FHI_DT_EnemyAccessory>(accessoryStruct.accessoryName, ContextString, true);
			if (Row)
			{
				FActorSpawnParameters spawnParameters;
				spawnParameters.Owner = this;
				AHIEnemyAccessory* enemyAccessory = UHIGameData::HIGetWerewolfWorld()->SpawnActor<AHIEnemyAccessory>(AHIEnemyAccessory::StaticClass(), spawnParameters);

				enemyAccessory->accessoryID = Row->accessoryID;
				enemyAccessory->accessoryName = accessoryStruct.accessoryName;
				enemyAccessory->accessoryMesh->SetStaticMesh(Row->accessoryMesh.LoadSynchronous());
				enemyAccessory->accessorySocketName = Row->accessorySocketName;
				enemyAccessory->HISetCollisionPreset(Row->collisionPresetName);
				enemyAccessory->isWeapon = Row->isWeapon;
				// Only active the first weapon
				if (enemyAccessory->isWeapon)
				{
					if (hasWeapon)
					{
						enemyAccessory->HISetActive(false);
					}
					else
					{
						enemyAccessory->HISetActive(true);
						actualWeapon = enemyAccessory;
						hasWeapon = true;
					}
				}
				else
				{
					enemyAccessory->isActive = true;
				}

				enemyAccessory->shootSocketName = Row->shootSocketName;
				enemyAccessory->shootAbilityTriggerTag = Row->shootAbilityTriggerTag;
				enemyAccessory->shootAbilityTag = Row->shootAbilityTag;
				enemyAccessory->attackProperties = Row->attackProperties;

				enemyAccessory->shootAbility = Row->shootAbility;
				// Add shootAbility to abilityList
				if (enemyAccessory->shootAbility)
				{
					abiliyList.Add(enemyAccessory->shootAbility);
					abilitySystem->GiveAbility(FGameplayAbilitySpec(enemyAccessory->shootAbility.GetDefaultObject(), 1, 0));
				}
				enemyAccessory->weaponCondition = accessoryStruct.weaponCondition;

				enemyAccessory->droppable = Row->droppable;
				enemyAccessory->dropAngle = Row->dropAngle;
				enemyAccessory->dropImpulse = Row->dropImpulse;
				enemyAccessory->HIAttachAccessoryToSocket(GetMesh());
				accessories.Add(enemyAccessory);
			}

		}

	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No Datatable accessories."));
	}

	ensure(hitOtherMuttonInRagdoll);
	hitOtherMuttonInRagdollRef = Cast<UGameplayEffect>(hitOtherMuttonInRagdoll->GetDefaultObject());

	ensure(changeDetectionMeterEffect);
	changeDetectionMeterEffectRef = Cast<UGameplayEffect>(changeDetectionMeterEffect->GetDefaultObject());

	DistanceDisableGERef = NewObject<UGameplayEffect>();



	DistanceDisableGERef->DurationPolicy = EGameplayEffectDurationType::Infinite;
	DistanceDisableGERef->InheritableGameplayEffectTags.AddTag(GET_GAMEPLAY_TAG(DISABLE_DISTANCE_TAG));
	DistanceDisableGERef->InheritableOwnedTagsContainer.AddTag(GET_GAMEPLAY_TAG(DISABLE_DISTANCE_TAG));
	DistanceDisableGERef->StackingType = EGameplayEffectStackingType::AggregateByTarget;
	DistanceDisableGERef->StackLimitCount = 1;

	UGameplayEffect* effect = NewObject<UGameplayEffect>();
	effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
	FScalableFloat time = 0.000001f;
	effect->DurationMagnitude = FGameplayEffectModifierMagnitude(time);
	effect->InheritableOwnedTagsContainer.AddTag(GET_GAMEPLAY_TAG(PATROL_TAG));
	FGameplayEffectContextHandle effectContextHandle;
	abilitySystem->ApplyGameplayEffectToSelf(effect, 0, effectContextHandle);
	effect->ConditionalBeginDestroy();

	bool isBoss = false;
	CHECK_HAS_TAG(abilitySystem, BOSS_TAG, isBoss);
	if (isBoss)
	{
		UHIGameData::HISetBoss(this);
	}
}

void AHIEnemy::HIAssignCharacterType()
{
	bool tagPresent = false;
	CHECK_HAS_TAG(abilitySystem, HUNTER_TAG, tagPresent);
	if (tagPresent)
	{
		HISetCharacterType(HUNTER);
		return;
	}

	HISetCharacterType(MUTTON);
}

void AHIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (HICheckDistance())
	{
		//for thrown enemies
		if (enemyToHit && !enemyHitted)
		{
			HIThrownRagdoll(DeltaTime);
		}
	}
}

FString AHIEnemy::HIGetVoiceString()
{
	FString voiceString;

	VOICE_ACTORS_CASE(voiceNameType, voiceString);

	return Super::HIGetVoiceString().Append(voiceString);
}

void AHIEnemy::HIHealthChanged(const FOnAttributeChangeData& Data)
{
	if (hudReference)
	{
		hudReference->HIChangeHealth(Data.NewValue);
	}
	if (Data.NewValue <= 0.f)
	{
		FGameplayTag tagDead = FGameplayTag::RequestGameplayTag(FName(TEXT("Character.Ability.Dead")), true);
		targetEnemyReference->HISetTargetImageVisibility(ESlateVisibility::Collapsed);
		abilitySystem->AddLooseGameplayTag(tagDead);
	}
}

void AHIEnemy::HIMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	if (hudReference)
	{
		hudReference->HIChangeMaxHealth(Data.NewValue);
	}
}

void AHIEnemy::HIspeedChanged(const FOnAttributeChangeData& Data)
{
	//if (
	// )
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Speed changed: %f"), Data.NewValue));
	//}
	GetCharacterMovement()->MaxWalkSpeed = enemiesAttributes->Getspeed();
}

void AHIEnemy::HIchargedValueChanged(const FOnAttributeChangeData& Data)
{
	if (hudReference)
	{
		hudReference->HIChangeFear(HIGetFear());
	}
}

void AHIEnemy::HIfearArmourChanged(const FOnAttributeChangeData& Data)
{
	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("fear Armour changed: %f"), Data.NewValue));
	}
}

void AHIEnemy::HIDetectionChanged(const FOnAttributeChangeData& Data)
{
	if (hudReference)
	{
		hudReference->HIChangeDetection(Data.NewValue);
	}
}

void AHIEnemy::HIActivateDelegates()
{
	enemyMaxHealthChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(enemiesAttributes->GetmaxHealthAttribute()).AddUObject(this, &AHIEnemy::HIMaxHealthChanged);
	enemyHealthChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(enemiesAttributes->GethealthAttribute()).AddUObject(this, &AHIEnemy::HIHealthChanged);
	enemySpeedChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(enemiesAttributes->GetspeedAttribute()).AddUObject(this, &AHIEnemy::HIspeedChanged);
	enemyFearChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(enemiesAttributes->GetchargedValueAttribute()).AddUObject(this, &AHIEnemy::HIchargedValueChanged);
	enemyDetectionChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(detectorComponent->HIGetDetectionAttributes()->GetdetectionValueAttribute()).AddUObject(this, &AHIEnemy::HIDetectionChanged);

}


void AHIEnemy::HIDeath()
{
	OnDeath.Broadcast();

	HIGreenDeath();

	for (AHIEnemyAccessory* accessory : accessories)
	{
		accessory->HIDetach();
	}

	UHIGameInstance* HIGM = Cast<UHIGameInstance>(GetGameInstance());
	HIGM->gameManager->CompletedRequisitMission(missionReq);

	patrolReference->HIRemoveEnemyFromPatrol(this);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Enemy.Grabbed"))))
	{
		HITurnIntoRagdoll();
		AHIWerewolf* wolf = UHIGameData::HIGetPlayerWerewolf();
		wolf->ThrowEnemy(this);
	}
	else
	{
		GetMesh()->SetSimulatePhysics(true);
		FVector launch = (this->GetActorLocation() - UHIGameData::HIGetWerewolfLocation());
		launch.Normalize();
		GetMesh()->AddImpulse(launch * 25000.f);
	}

	// Disable HUD
	hudReference->HIDisableHUD();
	abilitySystem->AddLooseGameplayTag(GET_GAMEPLAY_TAG(STOP_BT_TAG));



}

void AHIEnemy::HITurnIntoRagdoll()
{
	GetMesh()->SetAllBodiesBelowSimulatePhysics("Hips", true, false);
	physicAnimComponent->ToggleActive();
	GetCapsuleComponent()->SetWorldRotation(FRotator(45.f, 45.f, 45.f));
}

void AHIEnemy::HIThrownRagdoll(float _deltaTime)
{
	if (enemyToHit)
	{
		FVector launch = FMath::VInterpTo(GetActorLocation(), enemyToHit->GetActorLocation(), _deltaTime, 10.f);
		SetActorLocation(launch);

		if ((enemyToHit->GetActorLocation() - GetActorLocation()).Size() < 50)
		{
			GetMesh()->SetSimulatePhysics(true);
			launch.Normalize();
			GetMesh()->AddImpulse(launch * 25000.f);
			AHIWerewolf* wolf = Cast<AHIWerewolf>(GetWorld()->GetFirstPlayerController()->GetPawn());
			wolf->GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(hitOtherMuttonInRagdollRef, enemyToHit->GetAbilitySystemComponent(), 0.f, FGameplayEffectContextHandle());
			enemyHitted = true;
			enemyToHit = nullptr;

		}
	}
}

void AHIEnemy::HINavLinkPosition(FVector _EndPos)
{
	FGameplayEventData DataEvent;
	UHIAbilityData* abilityData = NewObject<UHIAbilityData>();
	abilityData->VectorPosition = _EndPos;
	DataEvent.OptionalObject = abilityData;

	FGameplayTag tagjump = FGameplayTag::RequestGameplayTag(FName(TEXT("Enemy.Trigger.ActivateJump")), true);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, tagjump, DataEvent);
}

void AHIEnemy::HITryLaunchGranade(FVector objetivePosition)
{


	if (HICanLaunchGrenade(objetivePosition))
	{
		FGameplayEventData DataEvent;
		UHIAbilityData* abilityData = NewObject<UHIAbilityData>();
		abilityData->VectorPosition = objetivePosition;
		DataEvent.OptionalObject = abilityData;

		FGameplayTag tagGrenade = FGameplayTag::RequestGameplayTag(FName(TEXT(GRANADE_LAUNCH_TAG)), true);
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, tagGrenade, DataEvent);
	}

}

bool AHIEnemy::HICanLaunchGrenade(FVector objetivePosition)
{
	UBlackboardComponent* blackboard = Cast<AAIController>(GetController())->GetBlackboardComponent();
	FBlackboard::FKey hintKey = blackboard->GetKeyID("WerewolfHint");
	FBlackboard::FKey werewolfKey = blackboard->GetKeyID("Werewolf");

	if (blackboard->IsValidKey(hintKey) == false || blackboard->IsValidKey(werewolfKey))
	{
		if (FVector::DistSquared(UHIGameData::HIGetWerewolfLocation(), objetivePosition) < launchGrenadeRadious * launchGrenadeRadious)
		{
			return true;
		}
	}

	return false;
}

void AHIEnemy::HIExitCombat()
{
	// Unassign alarm after exit combat
	HIUnassignAlarm();

	patrolReference->HIRemoveEnemyCombat(this);
}


void AHIEnemy::HISetNormalDetection()
{
	if (!abilitySystem->HasMatchingGameplayTag(GET_GAMEPLAY_TAG(DEAD_TAG)))
	{
		detectorComponent->HISetInitialDetection();
	}
}

void AHIEnemy::HIUnassignAlarm()
{
	// Remove tag combat_alarm
	FGameplayTagContainer enemyTags;
	abilitySystem->GetOwnedGameplayTags(enemyTags);
	if (enemyTags.HasTag(GET_GAMEPLAY_TAG(COMBAT_ALARM_TAG)))
	{
		abilitySystem->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(COMBAT_ALARM_TAG));
	}
	// If it isn't white mutton, unassign alarm
	if (!enemyTags.HasTag(GET_GAMEPLAY_TAG(WHITE_MUTTON_TAG)))
	{
		alarmAssigned = nullptr;
	}
}

bool AHIEnemy::HIIsbackToWall()
{

	FHitResult outHit;;
	FCollisionQueryParams collisionParams;

	bool hitt = GetWorld()->LineTraceSingleByChannel(outHit, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * -1.f) * 250.f, GAME_TRACE_BUILDING, collisionParams);

	if (hitt)
	{
		return true;
	}

	return false;
}

void AHIEnemy::HIAddAccessory(AHIEnemyAccessory* _accessoryToAdd)
{
	if (_accessoryToAdd)
	{
		accessories.Add(_accessoryToAdd);
	}
}

void AHIEnemy::HIChangeWeapon(int32 _weaponIDToChange)
{
	if (actualWeapon->accessoryID == _weaponIDToChange)
	{
		return;
	}

	AHIEnemyAccessory* enemyAccessory = HIGetAccessoryByID(_weaponIDToChange);
	if (enemyAccessory && enemyAccessory->isWeapon)
	{
		UBlackboardComponent* blackboard = Cast<AAIController>(GetController())->GetBlackboardComponent();
		blackboard->SetValueAsBool("ChangeWeapon", true);

		previousWeapon = actualWeapon;
		actualWeapon = enemyAccessory;
	}
}

AHIEnemyAccessory* AHIEnemy::HIGetAccessoryByID(int _accessoryID) const
{
	AHIEnemyAccessory* enemyAccessory = nullptr;
	for (AHIEnemyAccessory* accessory : accessories)
	{
		if (accessory->accessoryID == _accessoryID)
		{
			enemyAccessory = accessory;
			break;
		}
	}
	return enemyAccessory;
}

void AHIEnemy::HISetVisibility(bool isVisible)
{

	bool enemyHided = false;
	CHECK_HAS_TAG(abilitySystem, ENEMY_DISABLE_TAG, enemyHided);
	if (enemyHided == false)
	{
		if (isVisible == false)
		{
			abilitySystem->AddLooseGameplayTag(GET_GAMEPLAY_TAG(ENEMY_DISABLE_TAG));
		}
	}
	else
	{
		if (isVisible)
		{
			abilitySystem->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(ENEMY_DISABLE_TAG));
		}
	}

	RootComponent->SetVisibility(isVisible, true);/*
	GetMesh()->SetVisibility(disabled);
	actualWeapon->accessoryMesh->SetVisibility(disabled);*/
}

void AHIEnemy::PostInitProperties()
{
	Super::PostInitProperties();
	UHIGameData::HISetEnemyAccessoriesDatatable(accessoriesDataTable); // If the datatable is selected when editor opens
}

#if WITH_EDITOR
void AHIEnemy::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(AHIEnemy, accessoriesDataTable))
	{
		// @TODO: Set in another more generic place and do it only once
		UHIGameData::HISetEnemyAccessoriesDatatable(accessoriesDataTable);
	}
}
#endif

void AHIEnemy::HISetVulnerability(bool _val)
{
	if (hudReference)
	{
		hudReference->HISetVulnerability(_val);
	}
}

// void AHIEnemy::HISetTargetHUDVisibility(ESlateVisibility _visibility)
// {
//    if (targetEnemyReference)
//    {
//       targetEnemyReference->HISetTargetImageVisibility(_visibility);
//    }
// }


void AHIEnemy::HIUpdateTargetWaypoint()
{
	AHIPatrolPoint* targetWaypoint = HIGetTargetPoint();
	AHIPatrolPoint* nextWaypoint = masterSecurity->HIGetMinimumPathPatrolPoint(currentWaypoint, HIGetTargetPoint());

	if (nextWaypoint == targetWaypoint)
	{
		int routeLength = patrolReference->HIGetEnemyPatrol(this).targetPoints.Num();
		currentWaypoint = patrolReference->HIGetEnemyPatrol(this).targetPoints[targetWaypointIndex];
		targetWaypointIndex = (targetWaypointIndex + 1) % routeLength;
	}
	else
	{
		currentWaypoint = nextWaypoint;
	}
}

TArray<FName> AHIEnemy::HIGetEnemyAccessoriesRowNames()
{
	return UHIGameData::HIGetEnemyAccessoriesRowNames();
}

bool AHIEnemy::HICheckDistance()
{
	AHIEnemyController* pointer = GetController<AHIEnemyController>();
	if (pointer)
	{
		TArray<UActorComponent*> components;
		GetComponents(components, true);

		if (FVector::DistSquared(GetActorLocation(), UHIGameData::HIGetWerewolfLocation()) > TICKDISTANCE)
		{
			for (UActorComponent* iter : components)
			{
				iter->Deactivate();
			}

			abilitySystem->ApplyGameplayEffectToSelf(DistanceDisableGERef, 0, FGameplayEffectContextHandle());
			pointer->GetBrainComponent()->StopLogic(TEXT("Distance Disable"));
			//abilitySystem->AddLooseGameplayTag(GET_GAMEPLAY_TAG(DISABLE_DISTANCE_TAG));
			return false;
		}
		else
		{
			for (UActorComponent* iter : components)
			{
				iter->Activate();
			}
			FGameplayTagContainer containerRef;
			containerRef.AddTag(GET_GAMEPLAY_TAG(DISABLE_DISTANCE_TAG));
			abilitySystem->RemoveActiveEffectsWithAppliedTags(containerRef);
			//abilitySystem->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(DISABLE_DISTANCE_TAG));
			pointer->GetBrainComponent()->StartLogic();
			return true;
		}
	}
	return false;
}

FVector AHIEnemy::HIGetPatrolPosition()
{
	HIUpdateTargetWaypoint();

	AHIPatrolPoint* destinyPatrolPoint = masterSecurity->HIGetMinimumPathPatrolPoint(currentWaypoint, HIGetTargetPoint());
	arriveWaypoint = destinyPatrolPoint;
	if (destinyPatrolPoint)
	{
		return FVector(destinyPatrolPoint->GetActorLocation());
	}
	else
	{
		//If destinyPatrolPoint is null that means that there is not a way to go from current waypoint to target waypoint
		return GetActorLocation();
	}

}

FVector AHIEnemy::HIGetExecutionPosition(bool sameLevelExecution, bool& backExecution)
{
	float executionPointDistance = 0.f;

	if (sameLevelExecution)
	{
		executionPointDistance = executionSameLevelPoint->GetRelativeLocation().Size2D();
		FVector backExecutionPosition = GetActorLocation() + GetActorForwardVector() * -1.f * executionPointDistance;
		return backExecutionPosition;
	}

	executionPointDistance = executionTopLevelPoint->GetRelativeLocation().Size2D();
	FVector forwardExecutionPosition = GetActorLocation() + GetActorForwardVector() * executionPointDistance;
	FVector backExecutionPosition = GetActorLocation() + GetActorForwardVector() * -1.f * executionPointDistance;
	FVector werewolfPosition = UHIGameData::HIGetWerewolfLocation();


	if (FMath::RandBool())
	{
		backExecution = true;
		return backExecutionPosition;
	}
	else
	{
		backExecution = false;
		return backExecutionPosition;
	}
}

void AHIEnemy::HICalculateCombatBehaviour()
{
	patrolReference->HIAssignCombatBehaviour(this);
}

UHIDetectorActorComponent* AHIEnemy::HIGetDetectorComponent()
{
	return detectorComponent;
}

const float AHIEnemy::HIGetDetectionValue() const
{
	return detectorComponent->HIGetDetectionAttributes()->GetdetectionValue();
}

void AHIEnemy::HIChangeDetectionMeter(float _changeValue)
{
	FGameplayEffectContextHandle effectContextHandle;
	FGameplayEffectSpec effectSpec = FGameplayEffectSpec(changeDetectionMeterEffectRef, effectContextHandle);
	effectSpec.SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName(DETECTION_ATTRIBUTE_TAGS)), _changeValue);
	abilitySystem->ApplyGameplayEffectSpecToSelf(effectSpec);
}

AHIPatrolPoint* AHIEnemy::HIGetTargetPoint()
{
	if (patrolReference)
	{
		return patrolReference->HIGetEnemyPatrol(this).targetPoints[targetWaypointIndex];
	}

	return nullptr;
}

AHIPatrolPoint* AHIEnemy::HIGetArrivePoint()
{
	return arriveWaypoint;
}

const float AHIEnemy::HIGetFear() const
{
	return ChargedAttributteComponent->HIGetCurrentChargedValue();
}

const float AHIEnemy::HIGetMaxFear() const
{
	return float(ChargedAttributteComponent->HIGetMaxChargedValue());
}

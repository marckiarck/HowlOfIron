// Created by pablo, carlos

#include "HIPatrol.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemies/HIAlarm.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "Characters/VincentVolk/HIWerewolf.h"
#include "Components/CapsuleComponent.h"
#include "Game/HIGameData.h"
#include "HI_DT_Patrol.h"
#include "HIMacros.h"
#include "IA/HIMasterSecurity.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MapLogic/HISpawnPoint.h"
#include "Math/UnrealMathUtility.h"
#include "NavigationSystem.h"

AHIPatrol::AHIPatrol()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHIPatrol::BeginPlay()
{
	Super::BeginPlay();

	currentFleeingEnemies = 0;
	currentMovingEnemies = 0;
	currentShootingEnemies = 0;

	detectionGameplayEffect = NewObject<UGameplayEffect>();
}

void AHIPatrol::HILoadDatatable(FName rowName)
{
	if (datatable)
	{
		FString ContextString = TEXT("Data table context");
		FHI_DT_Patrol* Row = nullptr;

		Row = datatable->FindRow<FHI_DT_Patrol>(rowName, ContextString, true);
		if (Row == nullptr)
		{
			TArray<FName> RowNames = datatable->GetRowNames();
			Row = datatable->FindRow<FHI_DT_Patrol>(RowNames[0], ContextString, true);
		}

		maxShootDistance = Row->maxShootDistance;
		frequencyShoot = Row->frequencyShootbase;
		maxShootingEnemies = Row->maxEnemiesShooting;

		//@TODO: REFACTOR
		UHIGameData::frequencyShoot = Row->frequencyShootbase;
		//UHIGameData::dodgeProbability = Row->chanceDodge;
		chanceDodge = Row->chanceDodge;

	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No Datatable Patrol."));
	}
}

//calculate shoot frequency dependant of num of enemies in combat and makes them shoot by turns. If someone is in battle, alert the rest if not in battle already
void AHIPatrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (combatMembers.Num() > 0.f)
	{
		frequencyShootTimer = FMath::Min(frequencyShootTimer + DeltaTime, frequencyShoot);
		if (frequencyShootTimer >= frequencyShoot)
		{

			if (shootingEnemies.Num() != 0) 
			{
				for (AHIEnemy* it : shootingEnemies)
				{
					it->GetAbilitySystemComponent()->AddLooseGameplayTag(GET_GAMEPLAY_TAG(COMBAT_SHOOT_TAG));
				}

					shootingEnemies.Empty();
					frequencyShootTimer = 0.f;
			}
		}
		frequencyDodgeTimer = FMath::Min(frequencyDodgeTimer + DeltaTime, frequencyDodge);

	}

}

void AHIPatrol::HICalculateFrequency(AHIEnemy* _enemy)
{
	float frequencyenemy = Cast<UHIEnemiesAttributes>(_enemy->HIGetAttributes())->GetfrequencyShoot();
	frequencyShoot = ((frequencyenemy * (1.f / combatMembers.Num()) / 3.f) * 2.f) + frequencyenemy / 3.f;
}

bool AHIPatrol::HIShouldShoot(AHIEnemy* _enemy, FGameplayTagContainer enemyTags)
{
	HICalculateFrequency(_enemy);
	if (currentShootingEnemies >= maxShootingEnemies)
	{
		return false;
	}

	if (frequencyShootTimer < frequencyShoot)
	{
		return false;
	}

	if (enemyTags.HasTag(GET_GAMEPLAY_TAG(SHOOT_COOLDOWN_TAG)))
	{
		return false;
	}

	FHitResult hitResult = FHitResult();
	FCollisionQueryParams params;
	params.AddIgnoredActor(_enemy);
	GetWorld()->LineTraceSingleByChannel(hitResult, _enemy->GetActorLocation(), UHIGameData::HIGetWerewolfLocation(), ECC_Visibility, params);
	if (hitResult.Actor != UHIGameData::HIGetPlayerWerewolf())
	{
		return false;
	}

	return true;
}

void AHIPatrol::HICancelCombatBehaviour(AHIEnemy* _enemy)
{
	UAbilitySystemComponent* enemyAbilitySystem = _enemy->GetAbilitySystemComponent();
	FGameplayTagContainer enemyTags;
	enemyAbilitySystem->GetOwnedGameplayTags(enemyTags);

	if (enemyTags.HasTag(FGameplayTag::RequestGameplayTag(FName(COMBAT_FLEE_TAG))))
	{
		--currentFleeingEnemies;
	}

	if (enemyTags.HasTag(FGameplayTag::RequestGameplayTag(FName(COMBAT_SHOOT_TAG))))
	{
		--currentShootingEnemies;
	}
	if (enemyTags.HasTag(FGameplayTag::RequestGameplayTag(FName(COMBAT_MOVE_TAG))))
	{
		--currentMovingEnemies;
	}

	COMBAT_TAGS_EXECUTE_MACRO(REMOVE_GAMEPLAY_TAG);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void AHIPatrol::HIAssignCombatBehaviour(AHIEnemy* _enemy)
{
	const UHIEnemiesAttributes* enemyAttributes = _enemy->HIGetAttributes();
	UAbilitySystemComponent* enemyAbilitySystem = _enemy->GetAbilitySystemComponent();
	UBlackboardComponent* enemyBB = _enemy->GetController<AHIEnemyController>()->GetBlackboardComponent();


	FGameplayTagContainer enemyTags;
	enemyAbilitySystem->GetOwnedGameplayTags(enemyTags);


	if (enemyTags.HasAnyExact(UHIGameData::HIGetCombatTags()))
	{
		return;
	}



	if (shootingEnemies.Num() < maxShootingEnemies && !enemyAbilitySystem->HasMatchingGameplayTag(GET_GAMEPLAY_TAG(SHOOTING_TAG)) && FVector::Dist(UHIGameData::HIGetWerewolfLocation(), _enemy->GetActorLocation()) >= 150.f)
	{
		if (enemyBB->GetValueAsInt("CombatRing") != 3)
		{
			if (shootingEnemies.Contains(_enemy) == false)
			{
				shootingEnemies.Add(_enemy);
			}
		}
	}
}

void AHIPatrol::HIAddAlarm(AHIAlarm* _alarm)
{
	patrolAlarms.Add(_alarm);
	_alarm->HISetPatrolOwner(this);
}

AHIEnemy* AHIPatrol::HIGetNearestEnemy(FVector _position)
{
	float minDist = MAX_FLT;
	AHIEnemy* nearestEnemy = nullptr;
	for (AHIEnemy* enemy : patrolMembers)
	{
		UAbilitySystemComponent* enemyAbilitySystem = enemy->GetAbilitySystemComponent();
		FGameplayTagContainer enemyTags;
		enemyAbilitySystem->GetOwnedGameplayTags(enemyTags);

		// If it's another mutton (no white mutton), it's not calling an alarm and it's not a reinforcement
		FGameplayTagContainer muttonTags;
		muttonTags.AddTag(GET_GAMEPLAY_TAG(MUTTON_TAG));
		muttonTags.AddTag(GET_GAMEPLAY_TAG(GREEN_MUTTON_TAG));
		muttonTags.AddTag(GET_GAMEPLAY_TAG(YELLOW_MUTTON_TAG));
		if (enemyTags.HasAny(muttonTags) && !enemyTags.HasTag(GET_GAMEPLAY_TAG(COMBAT_ALARM_TAG)) && !enemyTags.HasTag(GET_GAMEPLAY_TAG(ENEMY_REINFORCEMENT_TAG)))
		{
			float dist = (enemy->GetActorLocation() - _position).Size();
			if (dist < minDist)
			{
				minDist = dist;
				nearestEnemy = enemy;
			}
		}
	}

	if (nearestEnemy)
	{
		// Set alarmPosition in blackboard
		UBlackboardComponent* blackboard = Cast<AAIController>(nearestEnemy->GetController())->GetBlackboardComponent();
		blackboard->SetValueAsVector("AlarmPosition", _position);
	}

	return nearestEnemy;
}

 const float AHIPatrol::HIGetDodgeChance() const
{
	return chanceDodge;
}

AHIMasterSecurity* AHIPatrol::HIGetMasterSecurity()
{
	return masterSecurity;
}

void AHIPatrol::HISetMasterSecurity(AHIMasterSecurity* _masterSecurity)
{
	masterSecurity = _masterSecurity;
}

void AHIPatrol::HISetRoutes(TArray<FHI_VigilanceRoute> newRoutesList)
{
	routes = newRoutesList;
	assignedRoutes.Empty();
	unassigendRoutes = newRoutesList;
	routesMap.Empty();
	patrolMembers.Empty(); //its assumned that if routes are overrided patrolMembers too
}

const TArray<AHIEnemy*> AHIPatrol::HIGetPatrolmembers() const
{
	return patrolMembers;
}

const FHI_VigilanceRoute AHIPatrol::HIGetEnemyPatrol(AHIEnemy* enemy) const
{
	return routesMap[enemy];
}

void AHIPatrol::HIAddEnemyToPatrol(AHIEnemy* addedEnemy)
{
	// If it is a reinforcement, add to patrol members without routes
	FGameplayTagContainer enemyTags;
	addedEnemy->GetAbilitySystemComponent()->GetOwnedGameplayTags(enemyTags);
	if (enemyTags.HasTag(GET_GAMEPLAY_TAG(ENEMY_REINFORCEMENT_TAG)))
	{
		patrolMembers.Add(addedEnemy);
	}
	else if (unassigendRoutes.Num() > 0)
	{
		FHI_VigilanceRoute newAssignedRoute = unassigendRoutes.Pop();
		assignedRoutes.Push(newAssignedRoute);
		routesMap.Add(addedEnemy, newAssignedRoute);

		patrolMembers.Add(addedEnemy);
	}
}

void AHIPatrol::HIRemoveEnemyFromPatrol(AHIEnemy* removedEnemy)
{
	HIRemoveEnemyCombat(removedEnemy);

	// If it is a reinforcement, remove only from patrol and combat members
	FGameplayTagContainer enemyTags;
	removedEnemy->GetAbilitySystemComponent()->GetOwnedGameplayTags(enemyTags);


	if (enemyTags.HasTag(GET_GAMEPLAY_TAG(ENEMY_REINFORCEMENT_TAG)))
	{
		patrolMembers.Remove(removedEnemy);
		combatMembers.Remove(removedEnemy);
	}
	if (routesMap.Contains(removedEnemy))
	{
		FHI_VigilanceRoute enemyRoute = routesMap[removedEnemy];
		assignedRoutes.Remove(enemyRoute);
		unassigendRoutes.Add(enemyRoute);
		routesMap.Remove(removedEnemy);
		patrolMembers.Remove(removedEnemy);
		combatMembers.Remove(removedEnemy);
	}

}

void AHIPatrol::HIAlertPatrolForCombat(AHIEnemy* _enemy)
{
	if (combatMembers.Contains(_enemy) == false)
	{
		if (combatMembers.Num() == 0)
		{
			// Activate alarms
			for (AHIAlarm* alarm : patrolAlarms)
			{
				alarm->HIActivate();
			}
		}
		HIAddEnemyCombat(_enemy);
	}
}

void AHIPatrol::HIAlertPatrolForHint(AHIEnemy* _enemy)
{
	AActor* detectedActor = _enemy->HIGetDetectorComponent()->HIGetDetectedActor();
	if (detectedActor)
	{
		FVector hintLocation = detectedActor->GetActorLocation();

		for (AHIEnemy* enemy : patrolMembers)
		{
			if (enemy != _enemy)
			{
				float randmuberX = FMath::RandRange(-500.f, 500.f);
				float randmuberY = FMath::RandRange(-500.f, 500.f);

				FVector hintRandom = hintLocation;
				hintRandom.X += randmuberX;
				hintRandom.Y += randmuberY;

				UBlackboardComponent* blackboard = Cast<AAIController>(enemy->GetController())->GetBlackboardComponent();
				blackboard->SetValueAsVector("WerewolfHint", hintRandom);
			}
		}
	}
	else
	{
		UBlackboardComponent* ownerblackboard = Cast<AAIController>(_enemy->GetController())->GetBlackboardComponent();
		FVector hintLocation = ownerblackboard->GetValueAsVector("WerewolfHint");

		for (AHIEnemy* enemy : patrolMembers)
		{
			if (enemy != _enemy)
			{
				float randmuberX = FMath::RandRange(-50.f, 50.f);
				float randmuberY = FMath::RandRange(-50.f, 50.f);

				FVector hintRandom = hintLocation;
				hintRandom.X += randmuberX;
				hintRandom.Y += randmuberY;

				UBlackboardComponent* blackboard = Cast<AAIController>(enemy->GetController())->GetBlackboardComponent();
				blackboard->SetValueAsVector("WerewolfHint", hintRandom);
			}
		}
	}
}

bool AHIPatrol::HICallForReinforcements(AHIEnemy* _enemy)
{
	// Find nearest spawn point
	TArray<AActor*> spawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHISpawnPoint::StaticClass(), spawnPoints);

	float nearestDistance = 999999.f;
	AHISpawnPoint* nearestSpawnPoint = nullptr;
	for (AActor* spawnPoint : spawnPoints)
	{
		float distanceToSpawnPoint = (spawnPoint->GetActorLocation() - _enemy->GetActorLocation()).Size();
		if (distanceToSpawnPoint < nearestDistance)
		{
			nearestDistance = distanceToSpawnPoint;
			nearestSpawnPoint = Cast<AHISpawnPoint>(spawnPoint);
		}
	}
	if (!nearestSpawnPoint)
	{
		return false;
	}

	// Spawn reinforcements
	for (FHIReinforcement reinforcement : _enemy->alarmAssigned->alarmReinforcements)
	{
		for (int i = 0; i < reinforcement.numOfReinforcements; ++i)
		{
			AHIEnemy* enemyToSpawn = Cast<AHIEnemy>(masterSecurity->SpawnEnemies(reinforcement.typeOfReinforcement));
			if (enemyToSpawn)
			{
				enemyToSpawn->patrolReference = this;
				enemyToSpawn->dataTableRow = 0;
				enemyToSpawn->masterSecurity = masterSecurity;
				enemyToSpawn->GetAbilitySystemComponent()->AddLooseGameplayTag(GET_GAMEPLAY_TAG(ENEMY_REINFORCEMENT_TAG));
				HIAddEnemyToPatrol(enemyToSpawn);
				masterSecurity->objectPooler->AddController(enemyToSpawn);

				// Remove tag Despawned
				FGameplayTagContainer enemyTags;
				enemyToSpawn->GetAbilitySystemComponent()->GetOwnedGameplayTags(enemyTags);
				if (enemyTags.HasTag(GET_GAMEPLAY_TAG(DESPAWNED_TAG)))
				{
					enemyToSpawn->GetAbilitySystemComponent()->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(DESPAWNED_TAG));
				}

				// Spawn
				FNavLocation spawnPointLocation;
				UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
				if (navSys)
				{
					navSys->GetRandomReachablePointInRadius(nearestSpawnPoint->GetActorLocation(), nearestSpawnPoint->radius, spawnPointLocation);
					// Tirar sweep
				}
				FVector locationSpawn = spawnPointLocation.Location;
				locationSpawn.Z += enemyToSpawn->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
				masterSecurity->objectPooler->spawnItem(enemyToSpawn, locationSpawn);

				enemyToSpawn->playerLastSeen = true;

				// Go to werewolf position when spawn
				AAIController* enemyController = Cast<AAIController>(enemyToSpawn->GetController());
				if (enemyController)
				{
					UBlackboardComponent* enemyBlackboard = enemyController->GetBlackboardComponent();
					if (enemyBlackboard)
					{
						enemyBlackboard->SetValueAsVector("WerewolfHint", UHIGameData::HIGetPlayerWerewolf()->GetActorLocation());
						enemyBlackboard->SetValueAsObject("Werewolf", UHIGameData::HIGetPlayerWerewolf());
						enemyBlackboard->SetValueAsFloat("DetectionValue", 100.f);
					}
				}
			}
		}
	}

	// Unassign alarm after use it
	_enemy->HIUnassignAlarm();

	return true;
}

void AHIPatrol::HIAddEnemyCombat(AHIEnemy* _enemy)
{
	if (combatMembers.Num() == 0)
	{
		masterSecurity->HIIncrementPatrolsInCombat();

		for (AHIEnemy* enemy : patrolMembers)
		{
			UBlackboardComponent* blackboard = Cast<AAIController>(enemy->GetController())->GetBlackboardComponent();

			UAbilitySystemComponent* enemyAbilitySystem = enemy->GetAbilitySystemComponent();

			UGameplayEffect* effect = NewObject<UGameplayEffect>();
			CREATE_GAMEPLAYEFFECT(effect, EGameplayModOp::Additive, UHIDetectionAttributes::GetdetectionValueAttribute(), 100.f);
			enemyAbilitySystem->ApplyGameplayEffectToSelf(effect, 1, FGameplayEffectContextHandle());
			effect->ConditionalBeginDestroy();

			blackboard->SetValueAsVector("WerewolfHint", UHIGameData::HIGetPlayerWerewolf()->GetActorLocation());
		}
	}
	combatMembers.Add(_enemy);
	UHIGameData::HIAddEnemyToCombatArray(_enemy);
	
	UpdateCombatVariables();

}

void AHIPatrol::UpdateCombatVariables()
{
	FString ContextString = TEXT("Data table context");
	FString stringName = FString::Printf(TEXT("%d_Enemy"), combatMembers.Num());
	FName datatableRowName = FName(*stringName);
	FHI_DT_Patrol* Row = datatable->FindRow<FHI_DT_Patrol>(datatableRowName, ContextString, true);
	if (Row)
	{
		HILoadDatatable(datatableRowName);
	}
	else {
		HILoadDatatable("Inf_Enemy");
	}
}

void AHIPatrol::HIRemoveEnemyCombat(AHIEnemy* _enemy)
{
	if (combatMembers.Num() > 0)
	{
		combatMembers.Remove(_enemy);
		UHIGameData::HIRemoveEnemyFromCombatArray(_enemy);
		AHIEnemyController* enemyController = _enemy->GetController<AHIEnemyController>();
		enemyController->GetBlackboardComponent()->ClearValue(FName("CombatRing"));

		UHIGameData::HIRemoveEnemyFromFirstArray(_enemy);
		UHIGameData::HIRemoveEnemyFromSecondArray(_enemy);

		if (combatMembers.Num() == 0)
		{
			// Unassign alarm to the enemies that have been assigned one and have not been in combat
			for (AHIEnemy* enemy : patrolMembers)
			{
				enemy->HIUnassignAlarm();
			}
			masterSecurity->HIDecrementPatrolsInCombat();
			alertAnim = false;
			combatAnim = false;
		}
	}

	UpdateCombatVariables();
}

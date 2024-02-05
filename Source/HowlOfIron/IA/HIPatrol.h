// Created by Pablo

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Engine/DataTable.h"
#include "Game/Patrol/HIPatrolPoint.h"
#include "HIPatrol.generated.h"


USTRUCT(BlueprintType)
struct FHIReinforcement
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Type of reinforcement"))
		TSubclassOf<AHIEnemy> typeOfReinforcement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Number of reinforcements of this type", ClampMin = 1, ClampMax = 20))
		int numOfReinforcements = 1;
};

USTRUCT(Blueprintable, BlueprintType)
struct FHI_VigilanceRoute : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Type Of Enemy"))
		TSubclassOf<AHIEnemy> spawnedActor;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Voice Actor"))
		TEnumAsByte<VoiceDatatableNamesType> voiceNameType = INVALID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (InlineEditConditionToggle))
		bool canCallForReinforcements = false;

	// @TODO: Check if the EditCondition of reinforcements can depend of spawnedActor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Reinforcements", EditCondition = "canCallForReinforcements", Tooltip = "(Only works for white muttons)"))
		TArray<FHIReinforcement> reinforcements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AHIPatrolPoint*> targetPoints;

	inline bool operator==(const FHI_VigilanceRoute& other) { return this->targetPoints == other.targetPoints; };
};

USTRUCT(Blueprintable, BlueprintType)
struct FHI_Patrols : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Row ID in the datatable"))
		FName PatrolDatatbleRow = FName(TEXT("NewRow"));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Patrol datatable"))
		UDataTable* patrolDatatable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FHI_VigilanceRoute> routes;
};
/**
 *
 */
UCLASS(Blueprintable)
class HOWLOFIRON_API AHIPatrol : public AActor
{
	GENERATED_BODY()


public:
	AHIPatrol();
	~AHIPatrol() { UE_LOG(LogTemp, Log, TEXT("Patrol script deleted.")); }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<AHIEnemy*> patrolMembers;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FHI_VigilanceRoute> routes;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float frequencyShoot;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float frequencyShootTimer;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float frequencyDodge = 4.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float frequencyDodgeTimer;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UDataTable* datatable;

	UPROPERTY()
		int enemyTurn;

	UPROPERTY()
		bool alertAnim;

	UPROPERTY()
		bool combatAnim;

protected:


private:
	UPROPERTY(VisibleAnywhere)
		TArray<FHI_VigilanceRoute> assignedRoutes;

	UPROPERTY(VisibleAnywhere)
		TArray<FHI_VigilanceRoute> unassigendRoutes;

	UPROPERTY(VisibleAnywhere)
		TMap<AHIEnemy*, FHI_VigilanceRoute> routesMap;

	UPROPERTY(VisibleAnywhere)
		TArray<AHIEnemy*> combatMembers;

	UPROPERTY(Transient)
		TArray<class AHIAlarm*> patrolAlarms;

	UPROPERTY(Transient)
	AHIMasterSecurity* masterSecurity;

#pragma region COMBAT_VARIABLES
	UPROPERTY()
		int maxFleeingEnemies;

	UPROPERTY()
		int currentFleeingEnemies;

	UPROPERTY()
		int maxShootingEnemies;

	UPROPERTY()
		int currentShootingEnemies;

	UPROPERTY()
		int maxMovingEnemies;

	UPROPERTY()
		int currentMovingEnemies;

	UPROPERTY()
		float maxShootDistance;

    UPROPERTY()
        float chanceDodge;


	UPROPERTY()
		TArray<AHIEnemy*> shootingEnemies;


	UPROPERTY(Transient)
		AHIEnemy* alarmEnemy;


	UPROPERTY(Transient)
		UGameplayEffect* detectionGameplayEffect;

#pragma endregion

public:

	UFUNCTION(BlueprintCallable)
		AHIMasterSecurity* HIGetMasterSecurity();

	UFUNCTION()
	void HISetMasterSecurity(AHIMasterSecurity* _masterSecurity);

	UFUNCTION()
		void HISetRoutes(TArray<FHI_VigilanceRoute> newRoutesList);

	UFUNCTION()
		const TArray<AHIEnemy*> HIGetPatrolmembers() const;

	UFUNCTION()
		const FHI_VigilanceRoute HIGetEnemyPatrol(AHIEnemy* enemy) const;

	UFUNCTION()
		void HIAddEnemyToPatrol(AHIEnemy* addedEnemy);

	UFUNCTION()
		void HIRemoveEnemyFromPatrol(AHIEnemy* removedEnemy);

	UFUNCTION()
		/// <summary>
		/// _enemy send his position to other patrol members and starts combat
		/// </summary>
		/// <param name="_enemy"> enemy preparing for combat </param>
		void HIAlertPatrolForCombat(AHIEnemy* _enemy);

	UFUNCTION()
		/// <summary>
		/// _enemy sends hint position to other patrol members
		/// </summary>
		/// <param name="_enemy"> enemy that alerts rest of teh patrol </param>
		void HIAlertPatrolForHint(AHIEnemy* _enemy);

	UFUNCTION()
		bool HICallForReinforcements(AHIEnemy* _enemy);

	void HIAddEnemyCombat(AHIEnemy* _enemy);

	void HIRemoveEnemyCombat(AHIEnemy* _enemy);

	UFUNCTION()
		void HILoadDatatable(FName rowName);

	UFUNCTION()
		void HICancelCombatBehaviour(AHIEnemy* _enemy);

	UFUNCTION()
		void HIAssignCombatBehaviour(AHIEnemy* _enemy);

	UFUNCTION()
		void HIAddAlarm(AHIAlarm* _alarm);

	/// <summary>
	/// Used to find the nearest enemy of the patrol to a position
	/// </summary>
	UFUNCTION()
		AHIEnemy* HIGetNearestEnemy(FVector _position);


		UFUNCTION(BlueprintCallable)
		const float HIGetDodgeChance() const;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void HICalculateFrequency(AHIEnemy* _enemy);

	UFUNCTION()
		bool HIShouldShoot(AHIEnemy* _enemy, FGameplayTagContainer enemyTags);

	void UpdateCombatVariables();
};

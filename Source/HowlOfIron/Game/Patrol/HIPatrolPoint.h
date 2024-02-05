// Created by pablo

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Task/HIWaitTask.h"
#include "HIPatrolPoint.generated.h"

class AHIEnemy;
class UBTTaskNode;
class UBehaviorTreeComponent;
class UHIWaypointTask;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskEnd, bool, _isSucces);



UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API AHIPatrolPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	AHIPatrolPoint();
	~AHIPatrolPoint() { UE_LOG(LogTemp, Log, TEXT("Targetpoint script deleted.")); }

public:

	UPROPERTY()
	FOnTaskEnd delegatewaypoint;

private:
	UPROPERTY(EditAnywhere, Category = "Patrol")
		TArray<AHIPatrolPoint*> neighbours;

	UPROPERTY(EditAnywhere, Instanced, Category = "Patrol", meta = (DisplayName = "WaypointTasksInstances"))
		TArray<UHIWaypointTask*> waypointTasks;

	UPROPERTY()
		bool taskStarted = false;

	UPROPERTY(Transient)
		class AHIEnemy* enemy;

public:
	const TArray<AHIPatrolPoint*> HIGetNeighbours() const;

	UFUNCTION()
	void HIAbortAction();

	UFUNCTION()
	 /// <summary>
	 /// Starts waypoint's tasks functionality
	 /// </summary>
	 /// <param name="_enemy"> Enemy associed to the waypoint tasks </param>
	 /// <returns> true if tasks are executed, false instead </returns>
	 bool HIArriveAction(AHIEnemy* _enemy);

	UFUNCTION()
		/// <summary>
		/// Function executed by the initial patrol point before return the substitute patrol point instead of the nearest point
		/// </summary>
		/// <return> Returns substitute patrol point </return>
		virtual AHIPatrolPoint* UpdateRequieredPatrolPoint();

	virtual void Tick(float DeltaTime) override;

	class AHIEnemy* const HIGetEnemyReference() { return enemy; }

protected:
	virtual void HISetEnemy(class AHIEnemy* newEnemy);


private:

#if WITH_EDITOR
	UFUNCTION()
		virtual bool ShouldTickIfViewportsOnly() const override;

	UFUNCTION()
		void HIEditorTick();

#endif


};

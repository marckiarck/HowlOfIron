// @AUTHOR: Carlos Fernandez

#include "HIEnemyTask_FindNearestDespawnPoint.h"
#include "MapLogic/HIDespawnPoint.h"

EBTNodeResult::Type UHIEnemyTask_FindNearestDespawnPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Find nearest despawn point
	TArray<AActor*> despawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHIDespawnPoint::StaticClass(), despawnPoints);

	float nearestDistance = 999999.f;
	AActor* nearestDespawnPoint = nullptr;
	for (AActor* despawnPoint : despawnPoints)
	{
		float distanceToDespawnPoint = (despawnPoint->GetActorLocation() - OwnerComp.GetOwner()->GetActorLocation()).Size();
		if (distanceToDespawnPoint < nearestDistance)
		{
			nearestDistance = distanceToDespawnPoint;
			nearestDespawnPoint = despawnPoint;
		}
	}
	if (!nearestDespawnPoint)
	{
		return EBTNodeResult::Failed;
	}
	
	// Set despawn point
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("DespawnPoint", nearestDespawnPoint->GetActorLocation());

	return EBTNodeResult::Succeeded;
}

FString UHIEnemyTask_FindNearestDespawnPoint::GetStaticDescription() const
{
	return TEXT("Find nearest despawn point");
}

// created by pablo... yes, I did it, bitch


#include "HIPatrolPoint.h"
#include <DrawDebugHelpers.h>
#include "Characters/Enemies/HIEnemy.h"
#include "Task/HIWaypointTask.h"

AHIPatrolPoint::AHIPatrolPoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

const TArray<AHIPatrolPoint*> AHIPatrolPoint::HIGetNeighbours() const
{

	return neighbours;
}



void AHIPatrolPoint::HIAbortAction()
{
	if (taskStarted)
	{

		for (UHIWaypointTask* iter : waypointTasks)
		{

			iter->HIAbortTask();

		}
	}
	taskStarted = false;
}

bool AHIPatrolPoint::HIArriveAction(AHIEnemy* _enemy)
{
	HISetEnemy(_enemy);

	if (waypointTasks.Num() == 0)
	{
		return false;
	}

	for (UHIWaypointTask* iter : waypointTasks)
	{
		iter->HIStartTask(_enemy, this);
		taskStarted = true;
	}

	return true;
}


void AHIPatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (taskStarted)
	{

		FVector cosa = enemy->GetActorLocation();
		bool taskFinished = true;

		for (UHIWaypointTask* iter : waypointTasks)
		{
			if (iter->HIIsExecuting())
			{
				iter->HIUpdateTask(DeltaTime);
				taskFinished = false;
			}
		}

		if (taskFinished)
		{
			taskStarted = false;
			delegatewaypoint.Broadcast(true);
		}
	}

#if WITH_EDITOR
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		HIEditorTick();
	}
#endif

}


AHIPatrolPoint* AHIPatrolPoint::UpdateRequieredPatrolPoint()
{
	return nullptr;
}

void AHIPatrolPoint::HISetEnemy(AHIEnemy* newEnemy)
{
	enemy = newEnemy;
}

#if WITH_EDITOR

bool AHIPatrolPoint::ShouldTickIfViewportsOnly() const
{
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		return true;
	}

	return false;
}

void AHIPatrolPoint::HIEditorTick()
{
	for (AHIPatrolPoint* neighbour : neighbours)
	{
		if (neighbour)
		{
			DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), neighbour->GetActorLocation(), 300.f, FColor::Magenta, false, -1.f, 0.f, 20.f);
		}
	}
}

#endif
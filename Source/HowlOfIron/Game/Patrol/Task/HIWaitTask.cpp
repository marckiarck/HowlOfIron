// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Patrol/Task/HIWaitTask.h"

UHIWaitTask::UHIWaitTask()
{

  
   // taskStarted = false;
}


void UHIWaitTask::HIStartTask(AHIEnemy* _enemy, AHIPatrolPoint* _waypoint)
{
    Super::HIStartTask(_enemy,_waypoint);
    elapsedWait = 0.f;
	
}

void UHIWaitTask::HIUpdateTask(float DeltaTime)
{
	if (HIIsExecuting())
	{
		elapsedWait += DeltaTime;		

		FRotator interpRot = FMath::RInterpConstantTo(enemy->GetActorRotation(), waypoint->GetActorRotation(), DeltaTime, rotationSpeed);
		FRotator actorRot = enemy->GetActorRotation();

		actorRot.Yaw = interpRot.Yaw;

		enemy->SetActorRotation(actorRot);

		if (elapsedWait >= waitTime)
		{			
            HIEndTask();
		}

	}
}



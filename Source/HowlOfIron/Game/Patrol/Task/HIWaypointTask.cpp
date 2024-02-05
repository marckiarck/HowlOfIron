// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Patrol/Task/HIWaypointTask.h"
#include "Game/Patrol/HIPatrolPoint.h"
#include "Characters/Enemies/HIEnemy.h"


void UHIWaypointTask::HIStartTask(AHIEnemy* _enemy, AHIPatrolPoint* _waypoint)
{
	executingTask = true;
	enemy = _enemy;
	waypoint = _waypoint;
}

void UHIWaypointTask::HIUpdateTask(float DeltaTime)
{
	HIEndTask();
}

void UHIWaypointTask::HIEndTask()
{
	executingTask = false;
}

void UHIWaypointTask::HIAbortTask()
{
	HIEndTask();
}

bool UHIWaypointTask::HIIsExecuting()
{
	return executingTask;
}

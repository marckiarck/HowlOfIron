// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Patrol/HISpawnPatrolPoint.h"

void AHISpawnPatrolPoint::BeginPlay()
{
	Super::BeginPlay();
}

AHIPatrolPoint* AHISpawnPatrolPoint::UpdateRequieredPatrolPoint()
{
	AHIEnemy* patrolpointEnemy = HIGetEnemyReference();
	if (conditionTrigered)
	{
		if (patrolpointEnemy)
		{
			patrolpointEnemy->HISetVisibility(true);
		}
	}
	else 
	{
		if (patrolpointEnemy)
		{
			patrolpointEnemy->HISetVisibility(false);
		}
	}

	return Super::UpdateRequieredPatrolPoint();
}

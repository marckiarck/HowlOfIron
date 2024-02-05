// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Patrol/HICinematicSpawnPatrolPoint.h"

void AHICinematicSpawnPatrolPoint::BeginPlay()
{
    Super::BeginPlay();

    for (UHICondition* conditionIter : startPatrolCondition)
    {
        UHIBlueprintCondition* blueprintCondition = Cast<UHIBlueprintCondition>(conditionIter);
        blueprintCondition->onConditionMet.AddDynamic(this, &AHICinematicSpawnPatrolPoint::HIEnableEnemy);
    }

    InitializeCinematicPoint();
}

TArray<UHICondition*> AHICinematicSpawnPatrolPoint::HIGetConditionPoints()
{
    return startPatrolCondition;
}

void AHICinematicSpawnPatrolPoint::HIEnableEnemy()
{
    AHIEnemy* patrolPointEnemy = HIGetEnemyReference();
    if (patrolPointEnemy)
    {
        patrolPointEnemy->HISetVisibility(true);
        conditionTrigered = true;
    }
}

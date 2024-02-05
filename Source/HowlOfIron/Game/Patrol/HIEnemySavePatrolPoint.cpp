// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Patrol/HIEnemySavePatrolPoint.h"
#include <Characters/Enemies/HIEnemy.h>

AHIEnemy* AHIEnemySavePatrolPoint::HIGetFirstEnemy()
{
	return firstEnemy;
}

void AHIEnemySavePatrolPoint::BeginPlay()
{
	Super::BeginPlay();

	eventCondition->onConditionTriggered.AddDynamic(this, &AHIEnemySavePatrolPoint::HIOnConditionChecked);
	eventCondition->HIInitialize();
	AHIConditionRegister::HIGetConditionRegister()->HIRegisterCondition(eventCondition, eventCondition->HIGetUnicBroadcast());
}

void AHIEnemySavePatrolPoint::HISetEnemy(AHIEnemy* newEnemy)
{
	Super::HISetEnemy(newEnemy);

	if (firstEnemy == nullptr)
	{
		firstEnemy = newEnemy;
	}
}

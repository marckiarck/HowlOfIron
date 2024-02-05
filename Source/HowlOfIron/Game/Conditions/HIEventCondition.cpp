// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Conditions/HIEventCondition.h"

void UHIEventCondition::HIAttachToEvent(FGenericEvent eventToAttach)
{
	eventToAttach.AddDynamic(this, &UHIEventCondition::HIOnEventCalled);
}

void UHIEventCondition::AttachToEnemyDeath(AHIEnemy* enemy)
{
	enemy->OnDeath.AddDynamic(this, &UHIEventCondition::HIOnEventCalled);
}

void UHIEventCondition::HIOnEventCalled()
{
	conditionMet = true;
}

bool UHIEventCondition::HICheckCondition()
{
	return conditionMet;
}

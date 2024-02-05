// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Conditions/HITriggerCondition.h"

UHITriggerCondition::UHITriggerCondition() : triggerActivated(false)
{

}

bool UHITriggerCondition::HICheckCondition()
{
	return triggerActivated;
}

void UHITriggerCondition::HIInitialize()
{
	ensureMsgf(targetTrigger, TEXT("There is a target trigger condition whith a None target trigger"));
	if (targetTrigger)
	{
		conditionTrigger = NewObject<UHIConditionTriggerEvent>();
		conditionTrigger->HISetListenerCondition(this);

		targetTrigger->AddTriggerEvent(conditionTrigger);
	}
}


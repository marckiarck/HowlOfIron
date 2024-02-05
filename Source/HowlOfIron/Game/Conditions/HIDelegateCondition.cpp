// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Conditions/HIDelegateCondition.h"

bool UHIDelegateCondition::HICheckCondition()
{
	bool conditionResult = condition->HICheckCondition();

	if (unicBroadcast)
	{
		if (conditionMet == false)
		{
			onConditionTriggered.Broadcast(conditionResult);
			conditionMet = conditionResult;
		}
	}
	else
	{
			onConditionTriggered.Broadcast(conditionResult);
	}

	return conditionResult;
}

void UHIDelegateCondition::HIInitialize()
{
	condition->HIInitialize();
}

void UHIDelegateCondition::HISetCondition(UHICondition* newCondition)
{
	condition = newCondition;
	condition->HIInitialize();
}

bool UHIDelegateCondition::HIGetUnicBroadcast()
{
	return unicBroadcast;
}

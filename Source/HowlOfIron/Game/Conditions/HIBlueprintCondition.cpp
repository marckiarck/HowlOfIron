// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Conditions/HIBlueprintCondition.h"

UHIBlueprintCondition::UHIBlueprintCondition()
{
	conditionMet = false;
}

bool UHIBlueprintCondition::HICheckCondition()
{
	return HICheckConditionBP_Implementation();
}

bool UHIBlueprintCondition::HICheckConditionBP_Implementation()
{
	return conditionMet;
}

void UHIBlueprintCondition::HISetConditionMet(bool newConditionMet)
{
	conditionMet = newConditionMet;

	if (conditionMet)
	{
		onConditionMet.Broadcast();
	}
}

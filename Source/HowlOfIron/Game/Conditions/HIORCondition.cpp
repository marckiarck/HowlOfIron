// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Conditions/HIORCondition.h"

bool UHIORCondition::HICheckCondition()
{
	for (UHICondition* iterCondition : conditionArray)
	{
		if (iterCondition->HICheckCondition())
		{
			return true;
		}
	}

	return false;
}

void UHIORCondition::HIInitialize()
{
	for (UHICondition* iterCondition : conditionArray)
	{
		iterCondition->HIInitialize();
	}
}

void UHIORCondition::HIAddCondition(UHICondition* addedCondition)
{
	addedCondition->HIInitialize();

	conditionArray.Add(addedCondition);
}

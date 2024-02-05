// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLogic/LevelLoading/HILevelLoadContext.h"

void UHILevelLoadContext::HIInitilaize()
{
	levelLoaded = false;

	for (UHICondition* iterCondition : conditionsToLoadLevel)
	{
		iterCondition->HIInitialize();
	}
}

void UHILevelLoadContext::HITryLoadLevel()
{
	if (levelLoaded)
	{
		return;
	}

	bool conditionsMeet = false;

	switch (conditonCheckMode)
	{
	case MEET_ANY_CONDITION:
	{
		conditionsMeet = HIMeetAnyCondition();
	}
	break;
	default:
	{
		conditionsMeet = HIMeetAllConditions();
	}
	}

	if (conditionsMeet)
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(UHIGameData::HIGetWerewolfWorld(), LevelToLoad, true, false, LatentInfo);
		levelLoaded = true;
	}
}

bool UHILevelLoadContext::HIMeetAllConditions()
{

	for (UHICondition* iterCondition : conditionsToLoadLevel)
	{
		if (iterCondition->HICheckCondition() == false)
		{
			return false;
		}
	}

	return true;
}

bool UHILevelLoadContext::HIMeetAnyCondition()
{
	for (UHICondition* iterCondition : conditionsToLoadLevel)
	{
		if (iterCondition->HICheckCondition())
		{
			return true;
		}
	}

	return false;
}

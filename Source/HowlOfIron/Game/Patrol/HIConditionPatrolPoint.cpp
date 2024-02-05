// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Patrol/HIConditionPatrolPoint.h"
#include "../Conditions/HITriggerCondition.h"

AHIConditionPatrolPoint::AHIConditionPatrolPoint()
{
	
}

void AHIConditionPatrolPoint::BeginPlay()
{
	Super::BeginPlay();

	for (UHICondition* iter : startPatrolCondition)
	{
		iter->HIInitialize();
	}

	conditionTrigered = false;
}

AHIPatrolPoint* AHIConditionPatrolPoint::UpdateRequieredPatrolPoint()
{

	if (conditionTrigered)
	{
		return nullptr;
	}else
	{

		bool conditionResult = false;
		for (UHICondition* iter : startPatrolCondition)
		{
			ensureMsgf(iter, TEXT("Iter is null. This may happend beacuse there is a condition in a condition point which is nullptr"));
			if (iter->HICheckCondition())
			{
				conditionResult = true;
			}
		}

		if (conditionResult)
		{
			conditionTrigered = true;
			return nullptr;
		}else
		{
			return this;
		}
	}
}

void AHIConditionPatrolPoint::HIInitializeConditions()
{

}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Patrol/HIConditionPatrolPoint.h"
#include "HISpawnPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API AHISpawnPatrolPoint : public AHIConditionPatrolPoint
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual AHIPatrolPoint* UpdateRequieredPatrolPoint() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Conditions/HICondition.h"
#include "HIInCombatCondition.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIInCombatCondition : public UHICondition
{
	GENERATED_BODY()
	
public:
	virtual bool HICheckCondition() override;
};

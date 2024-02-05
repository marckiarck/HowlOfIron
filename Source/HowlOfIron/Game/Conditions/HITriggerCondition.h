// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/PerceptionSystem/Detections/HIConeDetection.h"
#include "HICondition.h"
#include "Design/HIConditionTriggerEvent.h"
#include "Design/HICustomTrigger.h"
#include "HITriggerCondition.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
/// <summary>
/// Condition based on enter a trigger to return true
/// </summary>
class HOWLOFIRON_API UHITriggerCondition : public UHICondition
{
	GENERATED_BODY()

public:
	UHITriggerCondition();

public:
	UPROPERTY(BlueprintReadWrite)
	bool triggerActivated;

private:

	UPROPERTY(EditAnywhere)
	AHICustomTrigger* targetTrigger;

	UPROPERTY(Transient)
		class UHIConditionTriggerEvent* conditionTrigger;

public:
	virtual bool HICheckCondition() override;
	virtual void HIInitialize() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Design/HITriggerEvent.h"
#include "HIConditionTriggerEvent.generated.h"


UCLASS()
class HOWLOFIRON_API UHIConditionTriggerEvent : public UHITriggerEvent
{
	GENERATED_BODY()

private:
	UPROPERTY(Transient)
		class UHITriggerCondition* listenerCondition;

public:

	void HISetListenerCondition(UHITriggerCondition* newListenerCondition);
	virtual void CodeExecuteTriggerEvent() override;
};

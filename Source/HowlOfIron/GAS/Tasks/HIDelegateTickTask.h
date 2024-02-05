// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HIDelegateTickTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTickDelegate, float, elapsedTime,float, DeltaTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartDelegateTickTask);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndDelegateTickTask);

UCLASS()
class HOWLOFIRON_API UHIDelegateTickTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UHIDelegateTickTask();

private:
	float delegateDuration;
	float elapsedDelegateTime;
	float delegateCallFrecuency;
	float delegateFrecuencyElapsed;

	UPROPERTY(BlueprintAssignable)
		FTickDelegate delegateFunctionality;
	
	UPROPERTY(BlueprintAssignable)
		FEndDelegateTickTask onEnd;

	UPROPERTY(BlueprintAssignable)
		FStartDelegateTickTask onStart;

public:
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHIDelegateTickTask* HIDelegateTemporalTask(UGameplayAbility* OwningAbility, float _delegateDuration, float _delegateCallFrecuency = 0.f /*@pamam _delegateCallFrecuency: time passed beetween delegateFunctionality execution*/);

private:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
};

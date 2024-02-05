// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HISlomo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlomoEnded);

UCLASS()
class HOWLOFIRON_API UHISlomo : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UHISlomo();

private:
	float timeScale;
	float previousTimeDilation;
	float scaleDuration;
	float taskLifeTime;

	UPROPERTY(BlueprintAssignable)
		FOnSlomoEnded OnSlomoEnded;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHISlomo* HISetTimeScale(UGameplayAbility* OwningAbility, float _newTimeScale, float _scaleDuration);

private:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
};

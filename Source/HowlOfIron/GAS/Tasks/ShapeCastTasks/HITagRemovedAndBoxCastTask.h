// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "HITagRemovedAndBoxCastTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBoxHitDelegate, const FHitResult, HittedActor);

UCLASS()
class HOWLOFIRON_API UHITagRemovedAndBoxCastTask : public UAbilityTask_WaitGameplayTagRemoved
{
	GENERATED_BODY()
	
public:
	UHITagRemovedAndBoxCastTask();

private:
	FVector pos;
	FVector boxSize;

public:
	UPROPERTY(BlueprintAssignable)
		FBoxHitDelegate OnActive;

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHITagRemovedAndBoxCastTask* HICreateBoxAndWaitTagRemoved(UGameplayAbility* OwningAbility, FVector BoxSize, FVector _pos, FGameplayTag removedTag);

	virtual void TickTask(float DeltaTime) override;
};

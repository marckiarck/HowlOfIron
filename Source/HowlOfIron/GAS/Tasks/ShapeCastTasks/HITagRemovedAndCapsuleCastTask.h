// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "HITagRemovedAndCapsuleCastTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCapsuleHitDelegate, const FHitResult, HittedActor);

UCLASS()
class HOWLOFIRON_API UHITagRemovedAndCapsuleCastTask : public UAbilityTask_WaitGameplayTagRemoved
{
	GENERATED_BODY()
	
public:
	UHITagRemovedAndCapsuleCastTask();

private:
	FVector pos;
	float CapsuleRadius;
	float CapsuleHalfHeight;

public:
	UPROPERTY(BlueprintAssignable)
		FCapsuleHitDelegate OnActive;

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHITagRemovedAndCapsuleCastTask* HICreateCapsuleAndWaitTagRemoved(UGameplayAbility* OwningAbility, float CapsuleRadius, float CapsuleHalfHeight, FVector _pos, FGameplayTag removedTag);

	virtual void TickTask(float DeltaTime) override;
};

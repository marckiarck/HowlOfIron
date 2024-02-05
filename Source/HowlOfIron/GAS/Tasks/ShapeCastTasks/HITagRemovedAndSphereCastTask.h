// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "UObject/ObjectMacros.h"
#include "HITagRemovedAndSphereCastTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSphereHitDelegate, const FHitResult, HittedActor);

UCLASS()
class HOWLOFIRON_API UHITagRemovedAndSphereCastTask : public UAbilityTask_WaitGameplayTagRemoved
{
	GENERATED_BODY()

public:
	UHITagRemovedAndSphereCastTask();
	
private:
	FVector Pos;
	float Radius;

public:
	UPROPERTY(BlueprintAssignable)
		FSphereHitDelegate OnActive;

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHITagRemovedAndSphereCastTask* HICreateSphereAndWaitTagRemoved(UGameplayAbility* OwningAbility, float _radius, FVector _pos, FGameplayTag removedTag);

	virtual void TickTask(float DeltaTime) override;
};

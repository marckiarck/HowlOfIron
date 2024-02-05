// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include <AbilitySystemInterface.h>
#include "HIRemoveLooseTagTask.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIRemoveLooseTagTask : public UAbilityTask
{
	GENERATED_BODY()

private:
	FGameplayTagContainer removeTags;

	UPROPERTY(Transient)
	UAbilitySystemComponent* abilitySystem;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHIRemoveLooseTagTask* HIRemoveLooseTags(UGameplayAbility* OwningAbility, FGameplayTagContainer looseTags, UAbilitySystemComponent* affectedAbilitySystem);
	virtual void Activate() override;
};

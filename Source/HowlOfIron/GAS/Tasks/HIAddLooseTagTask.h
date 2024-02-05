// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include <AbilitySystemInterface.h>
#include "HIAddLooseTagTask.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIAddLooseTagTask : public UAbilityTask
{
	GENERATED_BODY()
	
private:
	FGameplayTagContainer addedTags;

	UPROPERTY(Transient)
		UAbilitySystemComponent* abilitySystem;


		UPROPERTY()
		bool DestroyAtEnd = false;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHIAddLooseTagTask* HIAddLooseTags(UGameplayAbility* OwningAbility, FGameplayTagContainer looseTags, UAbilitySystemComponent* affectedAbilitySystem, bool _destroyAtEnd = false);
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
};

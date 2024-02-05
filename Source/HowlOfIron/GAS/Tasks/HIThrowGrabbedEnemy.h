// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HIThrowGrabbedEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveThrow, AActor*, enemyThrown);

UCLASS()
class HOWLOFIRON_API UHIThrowGrabbedEnemy : public UAbilityTask
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintAssignable)
	FOnActiveThrow OnActive;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHIThrowGrabbedEnemy* HIThrowEnemyGrabbed(UGameplayAbility* OwningAbility);

private:
	virtual void Activate() override;
};

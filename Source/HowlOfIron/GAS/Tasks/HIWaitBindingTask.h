// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HIWaitBindingTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBindUsed);

UCLASS()
class HOWLOFIRON_API UHIWaitBindingTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UHIWaitBindingTask();
	~UHIWaitBindingTask() {};

private:
	FName bindingKey;

	FInputActionBinding functionBinding;

	UPROPERTY(Transient)
	APlayerController* playerController;

	UPROPERTY(BlueprintAssignable)
	FOnBindUsed OnBindingUsed;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHIWaitBindingTask* HIWaitBinding(UGameplayAbility* OwningAbility, FName bindingName);

private:
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	
	UFUNCTION()
	void OnBindUsed();
};

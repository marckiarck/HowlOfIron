// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HIChangeMaterialParameter.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIChangeMaterialParameter : public UAbilityTask
{
	GENERATED_BODY()

private:
	UPROPERTY(Transient)
	class USkeletalMeshComponent* mesh;

	UPROPERTY()
	FName variableName;

	UPROPERTY()
	float parameterValue;

	UPROPERTY()
	float previousValue;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHIChangeMaterialParameter* HIChangeMaterialParameter(UGameplayAbility* OwningAbility, USkeletalMeshComponent* _mesh, FName _variableName, float _parameterValue);

private:
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
};

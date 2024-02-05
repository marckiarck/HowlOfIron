// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include <Characters/HICharacterAttributes.h>
#include "HIChargedValueCalculation.generated.h"

struct HIChargedValueAttributeStruct
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(chargedValue)

	HIChargedValueAttributeStruct()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, chargedValue, Target, false);
	}
};

UCLASS()
class HOWLOFIRON_API UHIChargedValueCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

private:
	HIChargedValueAttributeStruct chargedValuesAttributes;

public:
	UHIChargedValueCalculation(const FObjectInitializer& objectInitializer);

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};

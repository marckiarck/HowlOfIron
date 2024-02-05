// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ExecutionCalculations/HIChargedValueCalculation.h"
#include "HIMacros.h"

UHIChargedValueCalculation::UHIChargedValueCalculation(const FObjectInitializer& objectInitializer)
{
	RelevantAttributesToCapture.Add(chargedValuesAttributes.chargedValueDef);
}

void UHIChargedValueCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	FGameplayEffectSpec spec = ExecutionParams.GetOwningSpec();

	float expectedChargeValue = spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName(CHARGED_ATTRIBUTE_TAGS)), false, -1.f);

	UAbilitySystemComponent* ChargedValueOwnerAbilitySystem = ExecutionParams.GetTargetAbilitySystemComponent();

	if (ChargedValueOwnerAbilitySystem && expectedChargeValue != -1.f)
	{
		FAggregatorEvaluateParameters evaluationParameters;

		float currentChargedValue = 0.f;
		ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(chargedValuesAttributes.chargedValueDef, evaluationParameters, currentChargedValue));

		if (currentChargedValue != expectedChargeValue)
		{
			float valueDiference = expectedChargeValue - currentChargedValue;
			FGameplayModifierEvaluatedData chargedValueModification = FGameplayModifierEvaluatedData(chargedValuesAttributes.chargedValueProperty, EGameplayModOp::Additive, valueDiference);
			OutExecutionOutput.AddOutputModifier(chargedValueModification);
		}
	}
}
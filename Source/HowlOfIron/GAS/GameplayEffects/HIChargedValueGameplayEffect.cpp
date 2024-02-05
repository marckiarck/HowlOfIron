// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayEffects/HIChargedValueGameplayEffect.h"
#include "../ExecutionCalculations/HIChargedValueCalculation.h"

UHIChargedValueGameplayEffect::UHIChargedValueGameplayEffect()
{
	FGameplayEffectExecutionDefinition chargedValueExecutionDefinition;
	chargedValueExecutionDefinition.CalculationClass = UHIChargedValueCalculation::StaticClass();
	this->Executions.Add(chargedValueExecutionDefinition);
}

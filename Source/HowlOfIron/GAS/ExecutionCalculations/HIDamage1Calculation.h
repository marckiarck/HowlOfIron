// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Characters/VincentVolk/HIWerewolfAttributes.h"
#include "HIMacros.h"
#include "HIDamage1Calculation.generated.h"



struct HIAttributeCaptureDamage1 
{
	HIDECLARE_ATTRIBUTE_CAPTUREDEF(damage1,Source);
	HIDECLARE_ATTRIBUTE_CAPTUREDEF(armour,Target);
	HIDECLARE_ATTRIBUTE_CAPTUREDEF(lifesteal,Source);
	HIDECLARE_ATTRIBUTE_CAPTUREDEF(health,Source);
	HIDECLARE_ATTRIBUTE_CAPTUREDEF(health,Target);
	HIDECLARE_ATTRIBUTE_CAPTUREDEF(maxHealth, Target);
	HIDECLARE_ATTRIBUTE_CAPTUREDEF(survivalMargin, Target);


	HIAttributeCaptureDamage1() 
	{
		HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, damage1, Source, false);
		HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, health, Target, false);
		HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, health, Source, false);
		HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, maxHealth, Target, false);
		HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHIWerewolfAttributes, armour, Target, false);
		HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHIWerewolfAttributes, lifesteal, Source, false);
		HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHIWerewolfAttributes, survivalMargin, Target, false);
	}
};

UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API UHIDamage1Calculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
private:
	HIAttributeCaptureDamage1 structAttributes;


public:
	UHIDamage1Calculation(const FObjectInitializer& objectInitializer);

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};

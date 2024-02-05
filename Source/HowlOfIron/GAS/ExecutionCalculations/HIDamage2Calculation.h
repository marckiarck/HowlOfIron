// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Characters/HICharacterAttributes.h"
#include "HIMacros.h"
#include "HIDamage2Calculation.generated.h"

struct HIAttributeCaptureDamage2
{
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(damage2, Source);
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(armour, Target);
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(lifesteal, Source);
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(health, Source);
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(health, Target);
	HIDECLARE_ATTRIBUTE_CAPTUREDEF(maxHealth, Target);
	HIDECLARE_ATTRIBUTE_CAPTUREDEF(survivalMargin, Target);

    HIAttributeCaptureDamage2()
    {
        HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, damage2, Source, false);
        HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, health, Target, false);
        HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, health, Source, false);
		HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, maxHealth, Target, false);
		HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHIWerewolfAttributes, armour, Target, false);
		HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHIWerewolfAttributes, lifesteal, Source, false);
		HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHIWerewolfAttributes, survivalMargin, Target, false);
    }
};

UCLASS()
class HOWLOFIRON_API UHIDamage2Calculation : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()

private:
    HIAttributeCaptureDamage2 structAttributes;
  

public:
    UHIDamage2Calculation(const FObjectInitializer& objectInitializer);

protected:
    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};

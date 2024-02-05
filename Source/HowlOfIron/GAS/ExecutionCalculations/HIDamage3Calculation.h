// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Characters/HICharacterAttributes.h"
#include "HIMacros.h"
#include "HIDamage3Calculation.generated.h"

struct HIAttributeCaptureDamage3
{
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(damage3, Source);
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(armour, Target);
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(lifesteal, Source);
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(health, Source);
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(health, Target);
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(maxHealth, Target);
    HIDECLARE_ATTRIBUTE_CAPTUREDEF(survivalMargin, Target);

    HIAttributeCaptureDamage3()
    {
        HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, damage3, Source, false);
        HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, health, Target, false);
        HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, health, Source, false);
        HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHICharacterAttributes, maxHealth, Target, false);
        HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHIWerewolfAttributes, armour, Target, false);
        HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHIWerewolfAttributes, lifesteal, Source, false);
        HIDEFINE_ATTRIBUTE_CAPTUREDEF(UHIWerewolfAttributes, survivalMargin, Target, false);
    }
};

UCLASS()
class HOWLOFIRON_API UHIDamage3Calculation : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()

private:
    HIAttributeCaptureDamage3 structAttributes;


public:
    UHIDamage3Calculation(const FObjectInitializer& objectInitializer);

protected:
    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};

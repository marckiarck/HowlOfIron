// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ExecutionCalculations/HIDamage1Calculation.h"
#include <GameplayEffectTypes.h>
#include <AbilitySystemComponent.h>




UHIDamage1Calculation::UHIDamage1Calculation(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
    RelevantAttributesToCapture.Add(structAttributes.damage1SourceDef);
    RelevantAttributesToCapture.Add(structAttributes.healthSourceDef);
    RelevantAttributesToCapture.Add(structAttributes.healthTargetDef);
	RelevantAttributesToCapture.Add(structAttributes.maxHealthTargetDef);
	RelevantAttributesToCapture.Add(structAttributes.armourTargetDef);
	RelevantAttributesToCapture.Add(structAttributes.lifestealSourceDef);
	RelevantAttributesToCapture.Add(structAttributes.survivalMarginTargetDef);

}

void UHIDamage1Calculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    FGameplayEffectSpec spec = ExecutionParams.GetOwningSpec();

    UAbilitySystemComponent* tragetAbilitySystem = ExecutionParams.GetTargetAbilitySystemComponent();
    UAbilitySystemComponent* werewolfAbilitySystem = ExecutionParams.GetSourceAbilitySystemComponent();

    if (werewolfAbilitySystem && tragetAbilitySystem)
    {
        FAggregatorEvaluateParameters evaluationParameters;

        float damage = 0.f;
        ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAttributes.damage1SourceDef, evaluationParameters, damage));

        float armour = 0.f;
        if (ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAttributes.armourTargetDef, evaluationParameters, armour))
        {
            damage = damage * (1 - armour);
        }




        float health = 0.f;
        ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAttributes.healthTargetDef, evaluationParameters, health));

        if (health - damage <= 0.f)
        {
			float survivalMargin = 0.f;
			if (ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAttributes.survivalMarginTargetDef, evaluationParameters, survivalMargin))
			{
				float maxHealth = 0.f;
				float surviveMarginHealth = 0.f;
				ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAttributes.maxHealthTargetDef, evaluationParameters, maxHealth));
				surviveMarginHealth = maxHealth * survivalMargin;
				if (health > surviveMarginHealth)
				{
					damage = health - surviveMarginHealth;
				}
				else
				{
					damage = health;
				}
			}
			else {
				damage = health;
			}
        }

        float lifesteal = 0.f;
        float lifehealed = 0.f;
        if (ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAttributes.lifestealSourceDef, evaluationParameters, lifesteal))
        {
            lifehealed = damage * lifesteal;
        }

        if (lifehealed > 0.f)
        {

            //UGameplayEffect* staticEffect = UHIGameData::HIGetStaticGameplayEffect();
            UGameplayEffect* staticEffect = NewObject<UGameplayEffect>();
            staticEffect->Modifiers.Empty();
            FGameplayModifierInfo modif = FGameplayModifierInfo();
            modif.ModifierOp = EGameplayModOp::Additive;
            modif.Attribute = structAttributes.healthSourceProperty;
            modif.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(lifehealed));
            staticEffect->Modifiers.Add(modif);
            ExecutionParams.GetSourceAbilitySystemComponent()->ApplyGameplayEffectToSelf(staticEffect, 1, FGameplayEffectContextHandle());
            staticEffect->ConditionalBeginDestroy();
        }


        FGameplayTag tagimmunity = FGameplayTag::RequestGameplayTag(FName(TEXT("Character.State.Immunity")), true);
        if (!ExecutionParams.GetTargetAbilitySystemComponent()->HasMatchingGameplayTag(tagimmunity))
        {
            FGameplayModifierEvaluatedData TargetHealthModification = FGameplayModifierEvaluatedData(structAttributes.healthTargetProperty, EGameplayModOp::Additive, -damage);
            OutExecutionOutput.AddOutputModifier(TargetHealthModification);
        }

    }

}
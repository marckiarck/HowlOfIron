// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_CheckInConeDuringTag.h"
#include <vector>
#include <GameplayTagContainer.h>

UHITask_CheckInConeDuringTag::UHITask_CheckInConeDuringTag()
{
    bTickingTask = true;
}

UHITask_CheckInConeDuringTag* UHITask_CheckInConeDuringTag::HICheckInConeDuringTag(UGameplayAbility* OwningAbility, TArray<AHIAbilityCharacter*>_charactersToCheck, float _lenght, float _coneAngle, FVector _emitterPos, FVector _coneDirection, TSubclassOf<UGameplayEffect> _damageGameplayEffect,/* TSubclassOf<UGameplayEffect> _removeDamageGameplayEffect,*/TSubclassOf<UGameplayEffect> _dotAddGameplayEffect, TSubclassOf<UGameplayEffect> _dotRemoveGameplayEffect, FGameplayTag _removedTag)
{
    UHITask_CheckInConeDuringTag* MyObj = NewAbilityTask<UHITask_CheckInConeDuringTag>(OwningAbility);
    MyObj->abilityCharactersToCheck = _charactersToCheck;
    MyObj->lenght = _lenght;
    MyObj->coneAngle = _coneAngle;
    MyObj->emitterPos = _emitterPos;
    MyObj->coneDirection = _coneDirection;
    MyObj->damageGameplayEffect = _damageGameplayEffect;
    //MyObj->removeDamageGameplayEffect = _removeDamageGameplayEffect;
    MyObj->dotAddGameplayEffect = _dotAddGameplayEffect;
    MyObj->dotRemoveGameplayEffect = _dotRemoveGameplayEffect;
    MyObj->Tag = _removedTag;
    return MyObj;
}

void UHITask_CheckInConeDuringTag::Activate()
{
Super::Activate();
    AHIAbilityCharacter* owner = Cast<AHIAbilityCharacter>(GetAvatarActor());

   
    for (AHIAbilityCharacter* it : abilityCharactersToCheck)
    {
        if (!((it) == owner))
        {
            UGameplayEffect* effect = (Cast<UGameplayEffect>(damageGameplayEffect->GetDefaultObject()));
            owner->GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(effect, it->GetAbilitySystemComponent());
            effect->ConditionalBeginDestroy();
        }
    }
}

void UHITask_CheckInConeDuringTag::TickTask(float DeltaTime)
{
Super::TickTask(DeltaTime);

    abilityCharactersInCone.Empty();
    AHIAbilityCharacter* owner = Cast<AHIAbilityCharacter>(GetAvatarActor());
    for (AHIAbilityCharacter* it : abilityCharactersToCheck)
    {
        if (!((it) == owner))
        {
            FVector itLocation;
            itLocation = it->GetActorLocation();
            FVector distToEmitter = itLocation - emitterPos;

            if (distToEmitter.Size() <= lenght)
            {
                distToEmitter.Normalize();
                float dotProduct = FVector::DotProduct(coneDirection, distToEmitter);
                float angleToConeDirection = FMath::RadiansToDegrees(FMath::Acos(dotProduct));
                if (angleToConeDirection < coneAngle)
                {
                    abilityCharactersInCone.Add(it);
                    FGameplayEffectContextHandle effectContextHandle;


                    UGameplayEffect* effect = (Cast<UGameplayEffect>(dotAddGameplayEffect->GetDefaultObject()));
                    //owner->GetAbilitySystemComponent()->ApplyGameplayEffectToTarget((Cast<UGameplayEffect>(damageGameplayEffect->GetDefaultObject())), it->GetAbilitySystemComponent());
                    owner->GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(effect, it->GetAbilitySystemComponent());
                    effect->ConditionalBeginDestroy();
                    //FGameplayEffectSpec effectSpec1 = FGameplayEffectSpec(Cast<UGameplayEffect>(damageGameplayEffect->GetDefaultObject()), effectContextHandle);
                    //it->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(effectSpec1, it->GetAbilitySystemComponent());
                    //FGameplayEffectSpec effectSpec2 = FGameplayEffectSpec(Cast<UGameplayEffect>(dotAddGameplayEffect->GetDefaultObject()), effectContextHandle);
                    //it->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(effectSpec2, it->GetAbilitySystemComponent());
                    /*it->GetAbilitySystemComponent()->AddLooseGameplayTag(GET_GAMEPLAY_TAG("Enemy.Ability.Ability2.dot"));*/
                }
                else
                {
                    float capsuleRadius = it->GetCapsuleComponent()->GetScaledCapsuleRadius();
                    distToEmitter = itLocation - emitterPos;
                    FVector itDirectionToCenterCone = coneDirection * distToEmitter;
                    itDirectionToCenterCone = itDirectionToCenterCone - itLocation;
                    itDirectionToCenterCone.Normalize();
                    FVector radiusPos = itLocation + (itDirectionToCenterCone * capsuleRadius);
                    FVector distToEmitterRadius = radiusPos - emitterPos;
                    if (distToEmitterRadius.Size() <= lenght)
                    {
                        distToEmitterRadius.Normalize();
                        dotProduct = FVector::DotProduct(coneDirection, distToEmitterRadius);
                        angleToConeDirection = FMath::RadiansToDegrees(FMath::Acos(dotProduct));

                        if (angleToConeDirection < coneAngle)
                        {
                            abilityCharactersInCone.Add(it);

                            UGameplayEffect* effect = (Cast<UGameplayEffect>(dotAddGameplayEffect->GetDefaultObject()));
                            owner->GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(effect, it->GetAbilitySystemComponent());     
                            effect->ConditionalBeginDestroy();
                        }
                        else
                        {
                            UGameplayEffect* effect = (Cast<UGameplayEffect>(dotRemoveGameplayEffect->GetDefaultObject()));
                            owner->GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(effect, it->GetAbilitySystemComponent());
                            effect->ConditionalBeginDestroy();
                        }
                    }
                }
            }
            else
            {
                UGameplayEffect* effect = (Cast<UGameplayEffect>(dotRemoveGameplayEffect->GetDefaultObject()));
                owner->GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(effect, it->GetAbilitySystemComponent());
                effect->ConditionalBeginDestroy();
            }
        }
    }

    if (abilityCharactersInCone.Num() >= 1)
    {
        onHit.Broadcast(abilityCharactersInCone);
    }
    else
    {
        noHit.Broadcast();
    }

}

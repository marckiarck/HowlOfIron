// Fill out your copyright notice in the Description page of Project Settings.


#include "HIEnemyTask_ActivateAbility.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "HIMacros.h"


EBTNodeResult::Type UHIEnemyTask_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
    AHIEnemy* enemy = enemyController->GetPawn<AHIEnemy>();


    UGameplayEffect* effect = NewObject<UGameplayEffect>();
    effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
    FScalableFloat time = 0.000001f;
    effect->DurationMagnitude = FGameplayEffectModifierMagnitude(time);
    //effect->DurationMagnitude = 0.000001f;
    effect->InheritableOwnedTagsContainer.AddTag(tagToAdd);
    FGameplayEffectContextHandle effectContextHandle;

    enemy->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(effect, 0, effectContextHandle);
    effect->ConditionalBeginDestroy();

//  FGameplayEffectSpec effectSpec = FGameplayEffectSpec(Cast<UGameplayEffect>(shootgameplayEffect->GetDefaultObject()), effectContextHandle);
//  enemy->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(effectSpec);
    return EBTNodeResult::Succeeded;

}

FString UHIEnemyTask_ActivateAbility::GetStaticDescription() const
{
    return FString(TEXT("Activate Ability"));
}

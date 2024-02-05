// Fill out your copyright notice in the Description page of Project Settings.


#include "HIEnemyTask_ActivateShootAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Characters/Enemies/HIEnemyAccessory.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "HIMacros.h"


EBTNodeResult::Type UHIEnemyTask_ActivateShootAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // @TODO: Don't create an effect here. Look for another way to launch the ability. FYI: We have access to the ability (enemy->actualWeapon->shootAbility) and we have the effects already created (in Game_Files/Characters/Enemies/Abilities/GameplayEffects/)
    
    AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
    AHIEnemy* enemy = enemyController->GetPawn<AHIEnemy>();

    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
    blackboard->ClearValue("ChangeWeapon");
    
    UGameplayEffect* effect = NewObject<UGameplayEffect>();
    effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
    FScalableFloat time = 0.000001f;
    effect->DurationMagnitude = FGameplayEffectModifierMagnitude(time);
    effect->InheritableOwnedTagsContainer.AddTag(enemy->actualWeapon->shootAbilityTriggerTag);
    FGameplayEffectContextHandle effectContextHandle;

    enemy->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(effect, 0, effectContextHandle);

    effect->ConditionalBeginDestroy();

    return EBTNodeResult::Succeeded;
}

FString UHIEnemyTask_ActivateShootAbility::GetStaticDescription() const
{
    return FString(TEXT("Activate Shoot ability"));
}

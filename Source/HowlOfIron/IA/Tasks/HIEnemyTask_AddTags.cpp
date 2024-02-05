// Fill out your copyright notice in the Description page of Project Settings.


#include "HIEnemyTask_AddTags.h"

EBTNodeResult::Type UHIEnemyTask_AddTags::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AHIEnemyController* muttonController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
    AHIEnemy* enemy = muttonController->GetPawn<AHIEnemy>();
    UAbilitySystemComponent* abilityComponent = enemy->GetAbilitySystemComponent();
    abilityComponent->AddLooseGameplayTags(tagContainer);
    return EBTNodeResult::Succeeded;
}

FString UHIEnemyTask_AddTags::GetStaticDescription() const
{
    return FString(TEXT("Add Tags"));
}

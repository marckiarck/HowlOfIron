// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIEnemyTask_RemoveTag.h"

EBTNodeResult::Type UHIEnemyTask_RemoveTag::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
    AHIEnemy* enemy = enemyController->GetPawn<AHIEnemy>();

   
    enemy->GetAbilitySystemComponent()->RemoveLooseGameplayTags(containerGameplayTags);

    return EBTNodeResult::Succeeded;
}

FString UHIEnemyTask_RemoveTag::GetStaticDescription() const
{
    return FString(TEXT("Remove Gameplays Tag"));
}

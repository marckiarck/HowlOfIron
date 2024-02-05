// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIEnemyTask_ClearBlackBoardValue.h"

EBTNodeResult::Type UHIEnemyTask_ClearBlackBoardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
    blackboard->ClearValue(clearKey.SelectedKeyName);
    return EBTNodeResult::Succeeded;
}

FString UHIEnemyTask_ClearBlackBoardValue::GetStaticDescription() const
{
    return FString(TEXT("Clear a BlackBoard Key"));
}

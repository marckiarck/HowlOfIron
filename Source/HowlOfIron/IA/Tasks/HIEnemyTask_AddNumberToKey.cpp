// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIEnemyTask_AddNumberToKey.h"
#include <BehaviorTree/Blackboard/BlackboardKeyType_Int.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Float.h>


UHIEnemyTask_AddNumberToKey::UHIEnemyTask_AddNumberToKey(const FObjectInitializer& ObjectInitializer)
{

    addKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UHIEnemyTask_AddNumberToKey, addKey));
    addKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UHIEnemyTask_AddNumberToKey, addKey));
}

EBTNodeResult::Type UHIEnemyTask_AddNumberToKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

    TSubclassOf<UBlackboardKeyType> tempkey = blackboard->GetKeyType(blackboard->GetKeyID(addKey.SelectedKeyName));


    if (tempkey == UBlackboardKeyType_Int::StaticClass())
    {
        int x = blackboard->GetValueAsInt(addKey.SelectedKeyName);
        x+= valueToKey;
        blackboard->SetValueAsInt(addKey.SelectedKeyName, x);
        return EBTNodeResult::Succeeded;

    }
    else if (tempkey == UBlackboardKeyType_Float::StaticClass())
    {
        float x = blackboard->GetValueAsFloat(addKey.SelectedKeyName);
        x += valueToKey;
        blackboard->SetValueAsFloat(addKey.SelectedKeyName, x);
        return EBTNodeResult::Succeeded;

    }
    return EBTNodeResult::Failed;
}

FString UHIEnemyTask_AddNumberToKey::GetStaticDescription() const
{
    return FString(TEXT("Add a value to Key"));
}

UHIEnemyTask_OverrideToKey::UHIEnemyTask_OverrideToKey(const FObjectInitializer& ObjectInitializer)
{
    addKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UHIEnemyTask_OverrideToKey, addKey));
    addKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UHIEnemyTask_OverrideToKey, addKey));
}

EBTNodeResult::Type UHIEnemyTask_OverrideToKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

    TSubclassOf<UBlackboardKeyType> tempkey = blackboard->GetKeyType(blackboard->GetKeyID(addKey.SelectedKeyName));


    if (tempkey == UBlackboardKeyType_Int::StaticClass())
    {
      
        blackboard->SetValueAsInt(addKey.SelectedKeyName, valueToKey);
        return EBTNodeResult::Succeeded;

    }
    else if (tempkey == UBlackboardKeyType_Float::StaticClass())
    {
  
        blackboard->SetValueAsFloat(addKey.SelectedKeyName, valueToKey);
        return EBTNodeResult::Succeeded;

    }
    return EBTNodeResult::Failed;
}

FString UHIEnemyTask_OverrideToKey::GetStaticDescription() const
{
    return FString(TEXT("Override a value to Key"));
}

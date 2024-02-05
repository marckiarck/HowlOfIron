// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIResetBlackboardValueTask.h"

EBTNodeResult::Type UHIResetBlackboardValueTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	blackboard->ClearValue(resetKey.SelectedKeyName);

	return EBTNodeResult::Succeeded;
}

FString UHIResetBlackboardValueTask::GetStaticDescription() const
{
	return FString(TEXT("Resets passed blackboard key"));
}

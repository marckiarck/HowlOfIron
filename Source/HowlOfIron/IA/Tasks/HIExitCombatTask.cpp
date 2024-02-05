// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIExitCombatTask.h"

EBTNodeResult::Type UHIExitCombatTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHIEnemyController* muttonController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = muttonController->GetPawn<AHIEnemy>();

	enemy->HIExitCombat();

	return EBTNodeResult::Succeeded;
}

FString UHIExitCombatTask::GetStaticDescription() const
{
	return FString(TEXT("Set enemy out of combat mode"));
}
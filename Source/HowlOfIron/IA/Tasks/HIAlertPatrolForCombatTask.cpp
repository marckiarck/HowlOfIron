// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIAlertPatrolForCombatTask.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "Characters/Enemies/HIEnemy.h"

EBTNodeResult::Type UHIAlertPatrolForCombatTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHIEnemyController* muttonController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = muttonController->GetPawn<AHIEnemy>();
	enemy->patrolReference->HIAlertPatrolForCombat(enemy);

	return EBTNodeResult::Succeeded;
}

FString UHIAlertPatrolForCombatTask::GetStaticDescription() const
{
	return FString(TEXT("Alert patrol partners"));
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIAlertPatrolForHintTask.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "Characters/Enemies/HIEnemy.h"

EBTNodeResult::Type UHIAlertPatrolForHintTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHIEnemyController* muttonController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = muttonController->GetPawn<AHIEnemy>();
	enemy->patrolReference->HIAlertPatrolForHint(enemy);

	return EBTNodeResult::Succeeded;
}

FString UHIAlertPatrolForHintTask::GetStaticDescription() const
{
	return FString(TEXT("Alert the rest of the patrol members that there is a werewolf hint"));
}

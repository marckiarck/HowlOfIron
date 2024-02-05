// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIUpdatePatrolPositionTaskNode.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "Characters/Enemies/HIEnemy.h"

EBTNodeResult::Type UHIUpdatePatrolPositionTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = Cast<AHIEnemy>(enemyController->GetPawn());

	if (enemy)
	{
		blackboard->SetValueAsVector("Position", enemy->HIGetPatrolPosition());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

FString UHIUpdatePatrolPositionTaskNode::GetStaticDescription() const
{
	return TEXT("Overrides in \"Position\" the position of the waypoint to go");
}

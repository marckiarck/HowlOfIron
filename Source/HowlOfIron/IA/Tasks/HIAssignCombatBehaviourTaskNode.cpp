// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIAssignCombatBehaviourTaskNode.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "Characters/Enemies/HIEnemy.h"

EBTNodeResult::Type UHIAssignCombatBehaviourTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = Cast<AHIEnemy>(enemyController->GetPawn());

	if (enemy)
	{
		enemy->HICalculateCombatBehaviour();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

FString UHIAssignCombatBehaviourTaskNode::GetStaticDescription() const
{
	return FString(TEXT("Gives tasks to enemy to decide wich action should do"));
}

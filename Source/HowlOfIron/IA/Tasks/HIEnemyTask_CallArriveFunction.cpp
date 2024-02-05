// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIEnemyTask_CallArriveFunction.h"
#include "Game/Patrol/HIPatrolPoint.h"
//#include "Game/Patrol/HIStaticAnimationPoint.h"

UHIEnemyTask_CallArriveFunction::UHIEnemyTask_CallArriveFunction()
{
	bNotifyTick = false;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UHIEnemyTask_CallArriveFunction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemyref = enemyController->GetPawn<AHIEnemy>();
	enemy = enemyref;

	ownerBT = &OwnerComp;

	if (enemy && enemy->HIGetArrivePoint())
	{

		if (enemy->HIGetArrivePoint()->HIArriveAction(enemy))
		{
			enemy->HIGetArrivePoint()->delegatewaypoint.AddDynamic(this, &UHIEnemyTask_CallArriveFunction::HIEndBehaviour);
			return EBTNodeResult::InProgress;
		}
		else
		{
			return EBTNodeResult::Succeeded;
		}
		

	}

	return EBTNodeResult::Failed;
}

FString UHIEnemyTask_CallArriveFunction::GetStaticDescription() const
{
	return FString(TEXT("Call a virtual function of ActualWayPoint"));
}

void UHIEnemyTask_CallArriveFunction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{


}

EBTNodeResult::Type UHIEnemyTask_CallArriveFunction::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (enemy && enemy->HIGetArrivePoint())
	{
		enemy->HIGetArrivePoint()->delegatewaypoint.RemoveDynamic(this, &UHIEnemyTask_CallArriveFunction::HIEndBehaviour);

		enemy->HIGetArrivePoint()->HIAbortAction();

	}
	return EBTNodeResult::Aborted;

}

void UHIEnemyTask_CallArriveFunction::HIEndBehaviour(bool _result)
{
		const UBTNode* cosa = ownerBT->GetActiveNode();
	if (_result)
	{
	
		ownerBT->OnTaskFinished(Cast<UBTTaskNode>(cosa), EBTNodeResult::Succeeded);
	}
	else
	{

		ownerBT->OnTaskFinished(Cast<UBTTaskNode>(cosa), EBTNodeResult::Failed);
	}

	enemy->HIGetArrivePoint()->delegatewaypoint.RemoveDynamic(this, &UHIEnemyTask_CallArriveFunction::HIEndBehaviour);
}

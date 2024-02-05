// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HITaskCheckMoveDistance.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "Characters/Enemies/HIEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UHITaskCheckMoveDistance::UHITaskCheckMoveDistance()
{

}

EBTNodeResult::Type UHITaskCheckMoveDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHIEnemyController* muttonController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = muttonController->GetPawn<AHIEnemy>();
	UBlackboardComponent* enemyBB = muttonController->GetBlackboardComponent();

	FVector newPosition = enemyBB->GetValueAsVector("EQSPosition");
	newPosition.Z = 0.f;
	FVector actualPosition = enemy->GetActorLocation();
	actualPosition.Z = 0.f;

	if (FVector::Dist(newPosition, actualPosition) < minDistanceToMove)
	{
		enemyBB->SetValueAsVector("EQSPosition", actualPosition);
	}

	return EBTNodeResult::Succeeded;
}

FString UHITaskCheckMoveDistance::GetStaticDescription() const
{
	return FString(TEXT("Check if the new Position of the EQS is too near"));
}

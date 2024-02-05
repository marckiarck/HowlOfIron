// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Services/HIAskActionToPatrol.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "Characters/Enemies/HIEnemy.h"

void UHIAskActionToPatrol::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = Cast<AHIEnemy>(enemyController->GetPawn());


	if (enemy)
	{
		enemy->HICalculateCombatBehaviour();
	}





}

FString UHIAskActionToPatrol::GetStaticDescription() const
{
	return FString(TEXT("Ask to Patrol what to do in every call"));
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HILaunchGrenadeTask.h"
#include <Characters/Enemies/HIEnemy.h>

EBTNodeResult::Type UHILaunchGrenadeTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = enemyController->GetPawn<AHIEnemy>();

	enemy->HITryLaunchGranade(UHIGameData::HIGetSteamPosition());

	return EBTNodeResult::Succeeded;
}

FString UHILaunchGrenadeTask::GetStaticDescription() const
{
	return FString(TEXT("Throws Grenade Ability To Werewolf"));
}

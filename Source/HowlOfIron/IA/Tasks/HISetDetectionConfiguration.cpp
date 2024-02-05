// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HISetDetectionConfiguration.h"

EBTNodeResult::Type UHISetDetectionConfiguration::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHIEnemyController* muttonController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = muttonController->GetPawn<AHIEnemy>();
	enemy->HIGetDetectorComponent()->HISetDetectionConfiguration(assigendDetection);

	return EBTNodeResult::Succeeded;
}

FString UHISetDetectionConfiguration::GetStaticDescription() const
{
	return FString(TEXT("Set a detection configuration to owner actor"));
}

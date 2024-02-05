// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Services/HIUpdateDetectionValueService.h"
#include <Game/PerceptionSystem/HIDetectorActorComponent.h>

void UHIUpdateDetectionValueService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = Cast<AHIEnemy>(enemyController->GetPawn());
	UHIDetectorActorComponent* ownerDetectorComponent = enemy->HIGetDetectorComponent();

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	blackboard->SetValueAsFloat(detectionValueKey.SelectedKeyName, ownerDetectorComponent->HIGetDetectionAttributes()->GetdetectionValue());
}

FString UHIUpdateDetectionValueService::GetStaticDescription() const
{
	return FString(TEXT("Saves detection value in selected blackboard key"));
}

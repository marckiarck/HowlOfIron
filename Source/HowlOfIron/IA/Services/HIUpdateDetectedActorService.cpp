// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Services/HIUpdateDetectedActorService.h"

void UHIUpdateDetectedActorService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = Cast<AHIEnemy>(enemyController->GetPawn());
	UHIDetectorActorComponent* ownerDetectorComponent = enemy->HIGetDetectorComponent();
	AActor* detectedActor = ownerDetectorComponent->HIGetDetectedActor();

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if (detectedActor)
	{
		blackboard->SetValueAsVector(detectedActorKey.SelectedKeyName, detectedActor->GetActorLocation());
	}
	
}

FString UHIUpdateDetectedActorService::GetStaticDescription() const
{
	return FString(TEXT("Saves detected actor in selected blackboard key"));
}

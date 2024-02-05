// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/MoveToPositionTaskNode.h"

EBTNodeResult::Type UMoveToPositionTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	blackboard = OwnerComp.GetBlackboardComponent();
	FVector targetPosition = blackboard->GetValueAsVector(targetPositionKey.SelectedKeyName);
	AAIController* actorController = Cast<AAIController>(OwnerComp.GetOwner());
	ACharacter* actor = Cast<ACharacter>(actorController->GetPawn());

	UAIBlueprintHelperLibrary::CreateMoveToProxyObject(GetWorld(), actorController->GetPawn(), targetPosition, nullptr, 1, true);

	AHIWerewolf* werewolf = UHIGameData::HIGetPlayerWerewolf();
	FVector Lookpos = FVector(werewolf->GetActorLocation().X, werewolf->GetActorLocation().Y, actor->GetActorLocation().Z);
	actor->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(actor->GetActorLocation(), Lookpos));

	return EBTNodeResult::Succeeded;
}

FString UMoveToPositionTaskNode::GetStaticDescription() const
{
	return TEXT("Move to a location looking at it");
}

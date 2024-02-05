// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIGetWerewolfTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Game/HIGameData.h"

void HIRotateToWerewolf(UBehaviorTreeComponent& OwnerComp)
{
	// Rotate to werewolf
	FVector rotationVector = UHIGameData::HIGetPlayerWerewolf()->GetActorLocation() - OwnerComp.GetOwner()->GetActorLocation();
	rotationVector.Z = OwnerComp.GetOwner()->GetActorLocation().Z;
	OwnerComp.GetOwner()->SetActorRotation(rotationVector.Rotation());
}

EBTNodeResult::Type UHIGetWerewolfTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	TSubclassOf<UBlackboardKeyType> tempkey = blackboard->GetKeyType(blackboard->GetKeyID(werewolfKey.SelectedKeyName));

    if (tempkey == UBlackboardKeyType_Object::StaticClass())
    {
        // Rotate to werewolf
        HIRotateToWerewolf(OwnerComp);

        // Set value in blackboard
        blackboard->SetValueAsObject(werewolfKey.SelectedKeyName, UHIGameData::HIGetPlayerWerewolf());
        return EBTNodeResult::Succeeded;

    }
    else if (tempkey == UBlackboardKeyType_Vector::StaticClass())
    {
		// Rotate to werewolf
		HIRotateToWerewolf(OwnerComp);

        // Set value in blackboard
        blackboard->SetValueAsVector(werewolfKey.SelectedKeyName, UHIGameData::HIGetPlayerWerewolf()->GetActorLocation());
        return EBTNodeResult::Succeeded;
    }

	return EBTNodeResult::Failed;
}

FString UHIGetWerewolfTask::GetStaticDescription() const
{
	return FString(TEXT("Saves a reference to the werewolf in passed blackboard key"));
}

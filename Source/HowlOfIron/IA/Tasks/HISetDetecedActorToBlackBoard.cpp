// Fill out your copyright notice in the Description page of Project Settings.


#include "HISetDetecedActorToBlackBoard.h"
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Object.h>

UHISetDetecedActorToBlackBoard::UHISetDetecedActorToBlackBoard(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{


   hintKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UHISetDetecedActorToBlackBoard, hintKey), AActor::StaticClass());
   hintKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UHISetDetecedActorToBlackBoard, hintKey));

}



EBTNodeResult::Type UHISetDetecedActorToBlackBoard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
    AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
    AHIEnemy* enemy = enemyController->GetPawn<AHIEnemy>();
    AActor* detectedActor = enemy->HIGetDetectorComponent()->HIGetDetectedActor();
    
  TSubclassOf<UBlackboardKeyType> tempkey =  blackboard->GetKeyType(blackboard->GetKeyID(hintKey.SelectedKeyName));


    if (detectedActor)
    {
        if (tempkey == UBlackboardKeyType_Object::StaticClass())
        {

            blackboard->SetValueAsObject(hintKey.SelectedKeyName, detectedActor);
            return EBTNodeResult::Succeeded;

        }
        else if (tempkey == UBlackboardKeyType_Vector::StaticClass())
        {
            blackboard->SetValueAsVector(hintKey.SelectedKeyName, detectedActor->GetActorLocation());
            return EBTNodeResult::Succeeded;

        }
    }
    return EBTNodeResult::Failed;
}

FString UHISetDetecedActorToBlackBoard::GetStaticDescription() const
{
    return FString(TEXT("Set detected Actor in a Blackboard Key"));
}

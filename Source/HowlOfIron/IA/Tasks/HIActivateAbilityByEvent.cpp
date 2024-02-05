// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/HIActivateAbilityByEvent.h"

EBTNodeResult::Type UHIActivateAbilityByEvent::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{


    AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
    AHIEnemy* enemy = enemyController->GetPawn<AHIEnemy>();

    FGameplayEventData DataEvent;   
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(enemy, tagToAdd, DataEvent);


    return EBTNodeResult::Succeeded;
}

FString UHIActivateAbilityByEvent::GetStaticDescription() const
{
    return FString(TEXT("Activate Ability by Event"));
}

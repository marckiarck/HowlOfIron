// Fill out your copyright notice in the Description page of Project Settings.


#include "HIEnemyTask_CheckAbilityIsActive.h"
#include "Characters/Enemies/HIEnemy.h"
#include <GameplayTagContainer.h>

UHIEnemyTask_CheckAbilityIsActive::UHIEnemyTask_CheckAbilityIsActive()
{
     bNotifyTick = true;
}

EBTNodeResult::Type UHIEnemyTask_CheckAbilityIsActive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AHIEnemyController* muttonController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
    AHIEnemy* enemy = muttonController->GetPawn<AHIEnemy>();
    UAbilitySystemComponent* abilityComponent = enemy->GetAbilitySystemComponent();
    FGameplayTagContainer ownerContainer;
    abilityComponent->GetOwnedGameplayTags(ownerContainer);



    if (ownerContainer.HasAny(tagContainer))
    {

        return EBTNodeResult::InProgress;
    }
    else
    {
        return EBTNodeResult::Succeeded;
    }
}


void UHIEnemyTask_CheckAbilityIsActive::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    AHIEnemyController* muttonController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
    AHIEnemy* enemy = muttonController->GetPawn<AHIEnemy>();
    UAbilitySystemComponent* abilityComponent = enemy->GetAbilitySystemComponent();
    FGameplayTagContainer ownerContainer;
    abilityComponent->GetOwnedGameplayTags(ownerContainer);



    if (!ownerContainer.HasAny(tagContainer))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}



FString UHIEnemyTask_CheckAbilityIsActive::GetStaticDescription() const
{
    return FString(TEXT("HI Check Ability Running"));
}

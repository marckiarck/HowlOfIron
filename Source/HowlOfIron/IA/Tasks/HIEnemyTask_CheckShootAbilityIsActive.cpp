// Fill out your copyright notice in the Description page of Project Settings.


#include "HIEnemyTask_CheckShootAbilityIsActive.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Characters/Enemies/HIEnemyAccessory.h"
#include "Characters/Enemies/HIEnemyController.h"
#include <GameplayTagContainer.h>

UHIEnemyTask_CheckShootAbilityIsActive::UHIEnemyTask_CheckShootAbilityIsActive()
{
     bNotifyTick = true;
}

EBTNodeResult::Type UHIEnemyTask_CheckShootAbilityIsActive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AHIEnemyController* muttonController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
    AHIEnemy* enemy = muttonController->GetPawn<AHIEnemy>();
    UAbilitySystemComponent* abilityComponent = enemy->GetAbilitySystemComponent();
    FGameplayTagContainer ownerContainer;
    abilityComponent->GetOwnedGameplayTags(ownerContainer);

    if (enemy->actualWeapon)
    {
        if (ownerContainer.HasTag(enemy->actualWeapon->shootAbilityTag))
        {

            return EBTNodeResult::InProgress;
        }
        else
        {
            return EBTNodeResult::Succeeded;
        }
    }
    else
    {
        return EBTNodeResult::Failed;
    }

}

void UHIEnemyTask_CheckShootAbilityIsActive::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    AHIEnemyController* muttonController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
    AHIEnemy* enemy = muttonController->GetPawn<AHIEnemy>();
    UAbilitySystemComponent* abilityComponent = enemy->GetAbilitySystemComponent();
    FGameplayTagContainer ownerContainer;
    abilityComponent->GetOwnedGameplayTags(ownerContainer);

    if (enemy->actualWeapon && !ownerContainer.HasTag(enemy->actualWeapon->shootAbilityTag))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}

FString UHIEnemyTask_CheckShootAbilityIsActive::GetStaticDescription() const
{
    return FString(TEXT("HI Check Shoot Ability Running"));
}

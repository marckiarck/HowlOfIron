
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIEnemyTask_CheckAbilityIsActive.generated.h"

class UAbilitySystemComponent;

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIEnemyTask_CheckAbilityIsActive : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UHIEnemyTask_CheckAbilityIsActive();
    
    public:

    UPROPERTY(EditAnywhere)
        FGameplayTagContainer tagContainer;
        
protected:

private:

    //UAbilitySystemComponent* abilityComponent;

public:

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

    virtual FString GetStaticDescription() const override;

    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

protected:

private:

};



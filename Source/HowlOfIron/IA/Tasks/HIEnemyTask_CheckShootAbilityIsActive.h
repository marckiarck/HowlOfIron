
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIEnemyTask_CheckShootAbilityIsActive.generated.h"

class UAbilitySystemComponent;

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIEnemyTask_CheckShootAbilityIsActive : public UBTTaskNode
{
    GENERATED_BODY()

public:
	UHIEnemyTask_CheckShootAbilityIsActive();

public:

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

    virtual FString GetStaticDescription() const override;

    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

protected:

private:

};



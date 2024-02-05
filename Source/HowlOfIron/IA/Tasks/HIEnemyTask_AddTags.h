// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIEnemyTask_AddTags.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIEnemyTask_AddTags : public UBTTaskNode
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere)
        FGameplayTagContainer tagContainer;

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

    virtual FString GetStaticDescription() const override;
};

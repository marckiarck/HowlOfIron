// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIEnemyTask_AddNumberToKey.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIEnemyTask_AddNumberToKey : public UBTTaskNode
{
	GENERATED_BODY()
	
        UHIEnemyTask_AddNumberToKey(const FObjectInitializer& ObjectInitializer);


    public:
    //Number To Add To a Float or int Key
    UPROPERTY(EditAnywhere)
    int valueToKey;

private:
    UPROPERTY(EditAnywhere)
    FBlackboardKeySelector addKey;

public:

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
    virtual FString GetStaticDescription() const override;

};


UCLASS()
class HOWLOFIRON_API UHIEnemyTask_OverrideToKey : public UBTTaskNode
{
    GENERATED_BODY()

        UHIEnemyTask_OverrideToKey(const FObjectInitializer& ObjectInitializer);


public:
    //Number To Add To a Float or int Key
    UPROPERTY(EditAnywhere)
        int valueToKey;

private:
    UPROPERTY(EditAnywhere)
        FBlackboardKeySelector addKey;

public:

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
    virtual FString GetStaticDescription() const override;

};

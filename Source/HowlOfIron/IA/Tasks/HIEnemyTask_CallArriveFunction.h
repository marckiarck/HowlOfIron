// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIEnemyTask_CallArriveFunction.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIEnemyTask_CallArriveFunction : public UBTTaskNode
{
    GENERATED_BODY()
    public:

    UHIEnemyTask_CallArriveFunction();




public:

protected:

private:
    UPROPERTY(Transient)
    UBehaviorTreeComponent* ownerBT;

	UPROPERTY(Transient)
		AHIEnemy* enemy;


public:

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

    virtual FString GetStaticDescription() const override;

    void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

    virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);


    UFUNCTION()
    void HIEndBehaviour(bool _result);
};

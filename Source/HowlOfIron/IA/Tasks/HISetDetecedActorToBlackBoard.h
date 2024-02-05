// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HISetDetecedActorToBlackBoard.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHISetDetecedActorToBlackBoard : public UBTTaskNode
{
    GENERATED_BODY()

public:

    UHISetDetecedActorToBlackBoard(const FObjectInitializer& ObjectInitializer);

private:

    UPROPERTY(EditAnywhere)
    FBlackboardKeySelector hintKey;

public:

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual FString GetStaticDescription() const override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIResetBlackboardValueTask.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIResetBlackboardValueTask : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector resetKey;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual FString GetStaticDescription() const override;
};

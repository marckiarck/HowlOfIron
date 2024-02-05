// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIGetWerewolfTask.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIGetWerewolfTask : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector werewolfKey;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual FString GetStaticDescription() const override;
};

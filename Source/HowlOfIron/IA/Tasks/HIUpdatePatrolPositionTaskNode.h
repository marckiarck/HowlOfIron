// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIUpdatePatrolPositionTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIUpdatePatrolPositionTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual FString GetStaticDescription() const override;
};

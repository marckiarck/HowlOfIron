// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HITaskCheckMoveDistance.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHITaskCheckMoveDistance : public UBTTaskNode
{
	GENERATED_BODY()


public:
	UHITaskCheckMoveDistance();
public:

	UPROPERTY(EditAnywhere)
	float minDistanceToMove = 200.f;

protected:

private:

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	virtual FString GetStaticDescription() const override;


protected:

private:
};

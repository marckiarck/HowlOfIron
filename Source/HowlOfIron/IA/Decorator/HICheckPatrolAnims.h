// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "HICheckPatrolAnims.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHICheckPatrolAnims : public UBTDecorator
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	bool checkCallAnim;

	UPROPERTY(EditAnywhere)
		bool checkAlertAnim;

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};

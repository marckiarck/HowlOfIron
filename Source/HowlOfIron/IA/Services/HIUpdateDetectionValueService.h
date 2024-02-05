// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "HIUpdateDetectionValueService.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIUpdateDetectionValueService : public UBTService
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector detectionValueKey;

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual FString GetStaticDescription() const override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "HIUpdateDetectedActorService.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIUpdateDetectedActorService : public UBTService
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector detectedActorKey;

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual FString GetStaticDescription() const override;
};

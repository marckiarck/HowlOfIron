// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "HIAskActionToPatrol.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIAskActionToPatrol : public UBTService
{
	GENERATED_BODY()
	
public:

public:

protected:
	
private:

public:

		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual FString GetStaticDescription() const override;

protected:

private:




};

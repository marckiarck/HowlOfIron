// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "HICheckCombatEnemies.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHICheckCombatEnemies : public UBTDecorator
{
    GENERATED_BODY()

public:

    UHICheckCombatEnemies();
    ~UHICheckCombatEnemies();

public:

protected:

private:
	UPROPERTY(EditAnywhere)
		int numCombatEnemies;

public:

virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:

private:




};

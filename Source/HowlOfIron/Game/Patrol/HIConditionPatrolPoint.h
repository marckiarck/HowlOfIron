// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Patrol/HIPatrolPoint.h"
#include "../Conditions/HICondition.h"
#include "Design/HICustomTrigger.h"
#include "HIConditionPatrolPoint.generated.h"

UENUM()
enum ConditionType {
	TRIGGER
};

UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API AHIConditionPatrolPoint : public AHIPatrolPoint
{
	GENERATED_BODY()

public:
	AHIConditionPatrolPoint();

public:
	virtual void BeginPlay() override;
	virtual AHIPatrolPoint* UpdateRequieredPatrolPoint() override;

protected:

private:
	void HIInitializeConditions();

protected:
	UPROPERTY(EditAnywhere, Instanced, Category = "Patrol| ConditionPoint")
		TArray<UHICondition*> startPatrolCondition;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Patrol| ConditionPoint")
		bool conditionTrigered;

};

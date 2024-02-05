// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Game/Patrol/HIConditionPatrolPoint.h>
#include <Game/Conditions/HIDelegateCondition.h>
#include "HIEnemySavePatrolPoint.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API AHIEnemySavePatrolPoint : public AHIConditionPatrolPoint
{
	GENERATED_BODY()

private:
	UPROPERTY(Transient)
		class AHIEnemy* firstEnemy = nullptr;

	UPROPERTY(EditAnywhere, Instanced)
		UHIDelegateCondition* eventCondition;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void HIOnConditionChecked(bool conditionResult);

	UFUNCTION(BlueprintImplementableEvent)
		void HIOnStopCondition(bool conditionResult);

	UFUNCTION(BlueprintPure)
	AHIEnemy* HIGetFirstEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void HISetEnemy(AHIEnemy* newEnemy) override;

};

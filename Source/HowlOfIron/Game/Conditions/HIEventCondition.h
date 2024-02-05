// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Conditions/HICondition.h"
#include <Game/HIGameData.h>
#include "HIEventCondition.generated.h"


UCLASS()
class HOWLOFIRON_API UHIEventCondition : public UHICondition
{
	GENERATED_BODY()

private:
	bool conditionMet = false;
	
public:
	UFUNCTION()
	void HIAttachToEvent(FGenericEvent eventToAttach);

	UFUNCTION(BlueprintCallable)
	void AttachToEnemyDeath(AHIEnemy* enemy);

	UFUNCTION()
	void HIOnEventCalled();

	virtual bool HICheckCondition() override;
};

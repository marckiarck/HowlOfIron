// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Conditions/HICondition.h"
#include "HIORCondition.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIORCondition : public UHICondition
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Instanced)
		TArray<UHICondition*> conditionArray;

public:
public:
	virtual bool HICheckCondition() override;
	virtual void HIInitialize() override;

	UFUNCTION(BlueprintCallable)
	void HIAddCondition(UHICondition* addedCondition);

};

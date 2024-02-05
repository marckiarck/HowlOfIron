// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Conditions/HICondition.h"
#include "HIBlueprintCondition.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConditionMet);

UCLASS()
class HOWLOFIRON_API UHIBlueprintCondition : public UHICondition
{
	GENERATED_BODY()

public:
	UHIBlueprintCondition();
	~UHIBlueprintCondition() {};

public:
	FOnConditionMet onConditionMet;

private:
	bool conditionMet;

public:
	virtual bool HICheckCondition() override;

	UFUNCTION(BlueprintNativeEvent)
	bool HICheckConditionBP();

	UFUNCTION(BlueprintCallable)
	void HISetConditionMet(bool newConditionMet);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Conditions/HICondition.h"
#include "HIDelegateCondition.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConditionTriggered, bool, conditionResult);

UCLASS()
class HOWLOFIRON_API UHIDelegateCondition : public UHICondition
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Instanced, meta = (ShowInnerProperties))
	UHICondition* condition;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Unic Broadcast", ToolTip = "If tick is active delegate will active just the first time the condition is met", ShowInnerProperties))
	bool unicBroadcast;

	UPROPERTY()
	bool conditionMet;

public:
	UPROPERTY(Transient)
		FOnConditionTriggered onConditionTriggered;

public:
	virtual bool HICheckCondition() override;
	virtual void HIInitialize() override;

	UFUNCTION(BlueprintCallable)
	void HISetCondition(UHICondition* newCondition);
	bool HIGetUnicBroadcast();
};

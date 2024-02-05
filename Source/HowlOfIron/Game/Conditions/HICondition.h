// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HICondition.generated.h"

/**
 *
 */
UCLASS(editinlinenew, DefaultToInstanced, BlueprintType, Blueprintable)
class HOWLOFIRON_API UHICondition : public UObject
{
	GENERATED_BODY()

public:
	virtual bool HICheckCondition();
	virtual void HIInitialize();
};


UCLASS()
class HOWLOFIRON_API UHITrueCondition : public UHICondition
{
	GENERATED_BODY()

public:
	virtual bool HICheckCondition() override;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "HICompareDistances.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHICompareDistances : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UHICompareDistances();

protected:
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};

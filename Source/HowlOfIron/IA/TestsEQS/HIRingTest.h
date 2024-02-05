// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "HIRingTest.generated.h"

/**
 * 
 */

UENUM()
enum EEnvTestRing 
{
	Ring1 = 1,
	Ring2 = 2,
	Ring3 = 3
};



UCLASS()
class HOWLOFIRON_API UEnvQueryTest_RingTest : public UEnvQueryTest
{
	GENERATED_BODY()


public:

	UEnvQueryTest_RingTest(const FObjectInitializer& ObjectInitializer);

public:

	UPROPERTY(EditDefaultsOnly, Category = Ring)
	TEnumAsByte<EEnvTestRing> RingToCheck;

protected:

private:
	

public:

protected:


	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

private:

	
};

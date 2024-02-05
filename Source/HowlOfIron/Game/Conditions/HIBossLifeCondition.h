// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Conditions/HICondition.h"
#include "HIBossLifeCondition.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIBossLifeCondition : public UHICondition
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnyWhere, meta = (ClampMin = "0", ClampMax = "1"))
		float lifePercent;

public:
	virtual bool HICheckCondition() override;
};

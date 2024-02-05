// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "HISpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API AHISpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	AHISpawnPoint();

public:
	UPROPERTY(VisibleAnywhere)
		class UHIComponentVisualizer* componentVisualizer;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 5000, Units = "cm"))
		float radius = 500.f;
};

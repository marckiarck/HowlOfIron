// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/PerceptionSystem/Detections/HIDetection.h"
#include "HIConeDetection.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIConeDetection : public UHIDetection
{
	GENERATED_BODY()

public:
	float maxConeDistance;
	float angleAperture;
	float coneHeight;
	float heightOffset;
	float steamDistance;

protected:
	virtual  UDetectionResult* HICalculateDetection(AActor* detectorActor)  override;
	virtual const float HICalculateHeuristic(float detectionValue) const override;
	virtual  void HIDrawDebug(AActor* detectorActor);
};

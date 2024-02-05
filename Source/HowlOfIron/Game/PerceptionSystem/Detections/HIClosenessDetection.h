// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/PerceptionSystem/Detections/HIDetection.h"
#include "HIClosenessDetection.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIClosenessDetection : public UHIDetection
{
	GENERATED_BODY()

public:
	float maxDetectionDistance;
	
protected:
	virtual UDetectionResult* HICalculateDetection(AActor* detectorActor) override;
	virtual const float HICalculateHeuristic(float detectionValue) const override;
};

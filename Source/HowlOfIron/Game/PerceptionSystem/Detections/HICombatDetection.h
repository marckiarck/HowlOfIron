// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/PerceptionSystem/Detections/HIClosenessDetection.h"
#include "HICombatDetection.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHICombatDetection : public UHIClosenessDetection
{
	GENERATED_BODY()

protected:
	virtual UDetectionResult* HICalculateDetection(AActor* detectorActor) override;

private:
	bool IsSteamInFrontOfDetectables(AActor* detectorActor);
};

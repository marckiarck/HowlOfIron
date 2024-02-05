// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HIDetectionConfiguration.h"
#include "HIDetectionDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FDetection
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TEnumAsByte<DetectionType> detection;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Weight"))
		float weight = 100.f;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Vision Angle", EditCondition = "detection==DetectionType::CONE", EditConditionHides))
		float visionAngle = 360.f;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Max vision distanace", EditCondition = "detection==DetectionType::CONE", EditConditionHides))
		float maxVisionDistance = 1500.f;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Cone Height", EditCondition = "detection==DetectionType::CONE", EditConditionHides))
		float coneHeight = 500.f;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Height Offset", EditCondition = "detection==DetectionType::CONE", EditConditionHides))
		float heightOffset = 100.f;

		//Distancia a la que el lowSteam deja de detectar
    UPROPERTY(EditAnywhere, meta = (DisplayName = "Steam Distance", EditCondition = "detection==DetectionType::CONE", EditConditionHides))
        float steamDistance = 100.f;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Max detection distance", EditCondition = "detection==DetectionType::CLOSENESS || detection==DetectionType::COMBAT", EditConditionHides))
		float maxDetectionDistance = 1500.f;
};

UCLASS()
class HOWLOFIRON_API UHIDetectionDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
	public:

		UPROPERTY(EditAnywhere, meta = (DisplayName = "Detections"))
		TArray<FDetection> detectionArray;
};

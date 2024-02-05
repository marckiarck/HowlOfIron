// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Detections/HIDetection.h"
#include "HIDetectionConfiguration.generated.h"

UENUM()
enum DetectionType {
    CONE,
    SOUND,
    CLOSENESS,
    COMBAT
};


UCLASS()
class HOWLOFIRON_API UHIDetectionConfiguration : public UObject
{
    GENERATED_BODY()

public:
    static UHIDetectionConfiguration* HICreateDetectionConfiguration(const class UHIDetectionDataAsset* detectionConfigurationAsset);

private:
    UPROPERTY()
        TArray<UHIDetection*> detections;

   

public:
    UDetectionResult* HIGetDetection(AActor* detectorActor);
  
private:
    static UHIDetection* HICreateDetection(struct FDetection detectionInfo);
};

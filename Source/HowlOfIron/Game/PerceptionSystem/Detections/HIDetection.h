// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HIDetection.generated.h"

/**
 *
 */

UCLASS()
class UDetectionResult : public UObject
{
    GENERATED_BODY()
public:
    UDetectionResult();

    float detectionValue = 0;
    AActor* detectionActor = nullptr;
};



UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API UHIDetection : public UObject
{
    GENERATED_BODY()
public:
    UHIDetection();



protected:
    float weight;

    UPROPERTY(Transient)
    UDetectionResult* detectionref;

private:


public:
     UDetectionResult* HIGetDetectionValue(AActor* detectorActor) ;
    void SetWeight(float newWeight);

protected:
    virtual  UDetectionResult* HICalculateDetection(AActor* detectorActor);
    virtual const float  HICalculateHeuristic(float detectionValue) const;
    virtual  void HIDrawDebug(AActor* detectorActor);

private:

 
};

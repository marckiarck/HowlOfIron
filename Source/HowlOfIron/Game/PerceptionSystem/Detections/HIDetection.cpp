// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PerceptionSystem/Detections/HIDetection.h"

UDetectionResult::UDetectionResult()
{
detectionActor = nullptr;
detectionValue=0.f;
}


UHIDetection::UHIDetection()
{
	detectionref = NewObject<UDetectionResult>();
}


UDetectionResult* UHIDetection::HIGetDetectionValue(AActor* detectorActor) 
{
	UDetectionResult* tempResult = HICalculateDetection(detectorActor);
	if (!tempResult)
	{
		return nullptr;
	}

	tempResult->detectionValue = HICalculateHeuristic(tempResult->detectionValue) * weight;

	if (UHIGameData::HIGetDebugMode())
	{
		HIDrawDebug(detectorActor);
	}

	return tempResult;
}

void UHIDetection::SetWeight(float newWeight)
{
	weight = newWeight;
}

 UDetectionResult* UHIDetection::HICalculateDetection(AActor* detectorActor) 
{
	//UDetectionResult* result = NewObject<UDetectionResult>();
	 detectionref->detectionActor=nullptr;
	 detectionref->detectionValue = 0.f;
	return detectionref;
}

const float UHIDetection::HICalculateHeuristic(float detectionValue) const
{
 return 0.f;
}

void UHIDetection::HIDrawDebug(AActor* detectorActor)
{
}



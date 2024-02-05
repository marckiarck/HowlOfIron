// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PerceptionSystem/Detections/HIClosenessDetection.h"
#include "Game/PerceptionSystem/HIDetectableActorComponent.h"

UDetectionResult* UHIClosenessDetection::HICalculateDetection(AActor* detectorActor)
{
	

	detectionref->detectionActor = nullptr;
	detectionref->detectionValue = 0.f;

	FVector distToDetectableActorVector;
	float distToDetectableActor = 0.f;

	float detection = MAX_FLT;
	for (AActor* detectableActor : DETECTABLE_ACTORS)
	{
		distToDetectableActorVector = detectableActor->GetActorLocation() - detectorActor->GetActorLocation();
		distToDetectableActor = distToDetectableActorVector.Size();

		if (distToDetectableActor <= maxDetectionDistance)
		{
			detection = FMath::Min(detection, distToDetectableActor);
			detectionref->detectionActor = detectableActor;
		}
	}

	detectionref->detectionValue = detection;
	return detectionref;
}

const float UHIClosenessDetection::HICalculateHeuristic(float detectionValue) const
{
	if (detectionValue == MAX_FLT)
	{
		return 0.f;
	}

	return FMath::Min((maxDetectionDistance - detectionValue) / maxDetectionDistance, 1.f);
}

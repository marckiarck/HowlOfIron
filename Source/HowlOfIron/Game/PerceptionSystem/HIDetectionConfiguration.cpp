// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PerceptionSystem/HIDetectionConfiguration.h"
#include "Game/PerceptionSystem/Detections/HIClosenessDetection.h"
#include "Game/PerceptionSystem/Detections/HIConeDetection.h"
#include "Game/PerceptionSystem/HIDetectionDataAsset.h"
#include "Detections/HICombatDetection.h"


UHIDetectionConfiguration* UHIDetectionConfiguration::HICreateDetectionConfiguration(const UHIDetectionDataAsset* detectionConfigurationAsset)
{
	UHIDetectionConfiguration* returnedDetectionConfiguration = NewObject<UHIDetectionConfiguration>();

	TArray<UHIDetection*> detections;
	for (FDetection detectionInfo : detectionConfigurationAsset->detectionArray)
	{
		returnedDetectionConfiguration->detections.Add(HICreateDetection(detectionInfo));
	}

	return returnedDetectionConfiguration;
}

UHIDetection* UHIDetectionConfiguration::HICreateDetection(FDetection detectionInfo)
{

	switch (detectionInfo.detection)
	{
	case DetectionType::CONE:
	{
		UHIConeDetection* coneDetection = NewObject<UHIConeDetection>();
		coneDetection->maxConeDistance = detectionInfo.maxVisionDistance;
		coneDetection->angleAperture = detectionInfo.visionAngle;
		coneDetection->coneHeight = detectionInfo.coneHeight;
		coneDetection->heightOffset = detectionInfo.heightOffset;
		coneDetection->steamDistance = detectionInfo.steamDistance;
		coneDetection->SetWeight(detectionInfo.weight);

		return coneDetection;
	}
	break;

	case DetectionType::SOUND:
	{
		return NewObject<UHIDetection>();;
	}
	break;

	case DetectionType::CLOSENESS:
	{
		UHIClosenessDetection* closenessDetection = NewObject<UHIClosenessDetection>();
		closenessDetection->SetWeight(detectionInfo.weight);
		closenessDetection->maxDetectionDistance = detectionInfo.maxDetectionDistance;

		return closenessDetection;
	}
	break;
	case  DetectionType::COMBAT:
	{
		UHICombatDetection* combatDetection = NewObject<UHICombatDetection>();
		combatDetection->SetWeight(detectionInfo.weight);
		combatDetection->maxDetectionDistance = detectionInfo.maxDetectionDistance;

		return combatDetection;
	}
	break;
	}

	return NewObject<UHIDetection>();;
}

UDetectionResult* UHIDetectionConfiguration::HIGetDetection(AActor* detectorActor)
{
	TArray<UDetectionResult*> detectedActors;


	for (UHIDetection* detection : detections)
	{
		UDetectionResult* resultTemp;

		resultTemp = detection->HIGetDetectionValue(detectorActor);
		if (detectedActors.Num() == 0)
		{
			detectedActors.Add(resultTemp);
		}
		else
		{
			TArray<UDetectionResult*> detectedActorsCopy = detectedActors;
			for (UDetectionResult* iter : detectedActorsCopy)
			{
				if (iter->detectionActor == resultTemp->detectionActor)
				{
					iter->detectionValue += resultTemp->detectionValue;
				}
				else
				{
					detectedActors.Add(resultTemp);
				}
			}
		}

	}




	UDetectionResult* aux = nullptr;
	float maxDetection = 0.f;

	for (UDetectionResult* iter : detectedActors)
	{
		if (maxDetection <= iter->detectionValue)
		{
			maxDetection = iter->detectionValue;
			aux = iter;
		}
	}

	return aux;
}

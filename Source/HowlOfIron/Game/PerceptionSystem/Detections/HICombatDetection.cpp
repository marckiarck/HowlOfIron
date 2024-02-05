// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PerceptionSystem/Detections/HICombatDetection.h"
#include <HIMacros.h>
#include <Characters/HICharacter.h>

UDetectionResult* UHICombatDetection::HICalculateDetection(AActor* detectorActor)
{
	detectionref->detectionActor = nullptr;
	detectionref->detectionValue = MAX_FLT;

	if (IsSteamInFrontOfDetectables(detectorActor))
	{
		return detectionref;
	}
	else {
		return Super::HICalculateDetection(detectorActor);
	}

}

bool UHICombatDetection::IsSteamInFrontOfDetectables(AActor* detectorActor)
{
	for (AActor* detectableActor : DETECTABLE_ACTORS) 
	{
		UWorld* world = detectorActor->GetWorld();
		AHICharacter* owner = Cast<AHICharacter>(detectorActor);
		FVector headLocation = owner->GetMesh()->GetSocketLocation("HeadSocket");

		FVector detectorLocation = detectorActor->GetActorLocation();
		FVector vectordireccion = (detectableActor->GetActorLocation() - detectorLocation).GetSafeNormal(0.f);
		FVector raypos = detectorLocation + (vectordireccion * maxDetectionDistance);

		FHitResult steamResult;
		FCollisionQueryParams collisionParams;
		collisionParams.AddIgnoredActor(detectorActor);
		if (world->LineTraceSingleByChannel(steamResult, headLocation, raypos, GAME_TRACE_STEAM, collisionParams))
		{
			if (steamResult.GetActor() != detectableActor)
			{
				return true;
			}
		}
		
	}

	return false;
}

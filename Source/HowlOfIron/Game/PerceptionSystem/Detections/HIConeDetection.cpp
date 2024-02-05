// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PerceptionSystem/Detections/HIConeDetection.h"
#include "CollisionQueryParams.h"
#include "Game/PerceptionSystem/HIDetectableActorComponent.h"
#include "DrawDebugHelpers.h"
#include "../Private/KismetTraceUtils.h"


UDetectionResult* UHIConeDetection::HICalculateDetection(AActor* detectorActor)
{
    

    detectionref->detectionActor = nullptr;
    detectionref->detectionValue = 0.f;
    AHICharacter* owner = Cast<AHICharacter>(detectorActor);

    FVector detectorLocation = detectorActor->GetActorLocation();
    FVector distToEmitterVector;
    float distToEmitter;
    FVector distToEmitterNormalized;
    FVector coneDirection = UKismetMathLibrary::GetForwardVector(owner->GetMesh()->GetSocketRotation("HeadSocket"));
    coneDirection.Z = 0.f;
    coneDirection.Normalize();
    FVector headLocation = owner->GetMesh()->GetSocketLocation("HeadSocket");
    

    float detection = MAX_FLT;

    for (AActor* detectableActor : DETECTABLE_ACTORS)
    {
        FVector detectableActorLocation = detectableActor->GetActorLocation();
        IAbilitySystemInterface* interfaceDetectable = Cast<IAbilitySystemInterface>(detectableActor);

        ensure(interfaceDetectable);

        UAbilitySystemComponent* abilitydetectable = interfaceDetectable->GetAbilitySystemComponent();



        //Check angle
        distToEmitterVector = detectableActorLocation - detectorLocation;
        distToEmitterNormalized = distToEmitterVector.GetSafeNormal(0.f);
        float dotProduct = FVector::DotProduct(coneDirection, distToEmitterNormalized);
        float angleToConeDirection = FMath::RadiansToDegrees(FMath::Acos(dotProduct));

        if (angleToConeDirection > angleAperture)
        {
            break;
        }

        //Height check
        FVector topDetectionHeigth = detectorActor->GetActorUpVector();
        topDetectionHeigth.Z *= (coneHeight + heightOffset);
        topDetectionHeigth += detectorActor->GetActorLocation();
        FVector downDetectionHeight = detectorActor->GetActorUpVector();
        downDetectionHeight.Z *= heightOffset;
        downDetectionHeight += detectorActor->GetActorLocation();
        if (detectableActorLocation.Z > topDetectionHeigth.Z)
        {
            break;
        }

        if (detectableActorLocation.Z < downDetectionHeight.Z)
        {
            break;
        }


        //DistanceCheck
        distToEmitter = distToEmitterVector.Size();
        if (distToEmitter < maxConeDistance)
        {
            //passed
        }
        else
        {
            break;
        }

        //Raycast check
        FVector vectordireccion = (detectableActorLocation - detectorLocation).GetSafeNormal(0.f);
        FVector raypos = detectorLocation + (vectordireccion * maxConeDistance);
        UWorld* world = detectorActor->GetWorld();

        FHitResult hitResult;
        FCollisionQueryParams collisionParams;
        collisionParams.AddIgnoredActor(detectorActor);

        if (world->LineTraceSingleByChannel(hitResult, headLocation, raypos, ECC_Visibility, collisionParams) /*== false*/)
        {
            FHitResult SteamResult;
            if (world->LineTraceSingleByChannel(SteamResult, headLocation, raypos, GAME_TRACE_STEAM ,collisionParams))
            {
                if (hitResult.GetActor() == detectableActor && SteamResult.GetActor() == detectableActor)
                {
                    detection = FMath::Min(distToEmitter, detection);
                    detectionref->detectionActor = detectableActor;
                }

            }
        }

        if (abilitydetectable->HasMatchingGameplayTag(GET_GAMEPLAY_TAG(HIGHSTEAM_TAG)))
        {
            detection = MAX_FLT;
        }
        else if (abilitydetectable->HasMatchingGameplayTag(GET_GAMEPLAY_TAG(LOWSTEAM_TAG)))
        {
            if (distToEmitter > steamDistance)
            {
                detection = MAX_FLT;
            }
            else
            {
                detection = (detection / 2.0f);
            }
        }
    }

    detectionref->detectionValue = detection;
    return detectionref;
}

const float UHIConeDetection::HICalculateHeuristic(float detectionValue) const
{
    if (detectionValue == MAX_FLT)
    {
        return 0.f;
    }

    return FMath::Min((maxConeDistance - detectionValue) / maxConeDistance, 1.f);
}

void UHIConeDetection::HIDrawDebug(AActor* detectorActor)
{
    AHICharacter* owner = Cast<AHICharacter>(detectorActor);
    FVector detectorLocation = detectorActor->GetActorLocation();
    FVector coneDirection = UKismetMathLibrary::GetForwardVector(owner->GetMesh()->GetSocketRotation("HeadSocket"));
    coneDirection.Z = 0.f;
    coneDirection.Normalize();
    FVector headLocation = owner->GetMesh()->GetSocketLocation("HeadSocket");

    DrawDebugLine(detectorActor->GetWorld(), headLocation, headLocation + coneDirection * maxConeDistance, FColor::Blue);

    FRotator rightRotator = FRotator(0.f, angleAperture, 0.f);
    FVector rightAngleVector = rightRotator.RotateVector(coneDirection);

    FRotator leftRotator = FRotator(0.f, -angleAperture, 0.f);
    FVector leftAngleVector = leftRotator.RotateVector(coneDirection);

    FVector topDetectionHeigth = detectorActor->GetActorUpVector();
    topDetectionHeigth.Z *= (coneHeight + heightOffset);
    topDetectionHeigth += detectorLocation;
    FVector downDetectionHeight = detectorActor->GetActorUpVector();
    downDetectionHeight.Z *= heightOffset;
    downDetectionHeight += detectorLocation;

    //Base of the "cacke"

    FVector baseRight = topDetectionHeigth + rightAngleVector * maxConeDistance;
    FVector baseLeft = topDetectionHeigth + leftAngleVector * maxConeDistance;
    DrawDebugLine(detectorActor->GetWorld(), topDetectionHeigth, baseRight, FColor::Yellow, false, -1.f, 0, 10.f);
    DrawDebugLine(detectorActor->GetWorld(), topDetectionHeigth, baseLeft, FColor::Yellow, false, -1.f, 0, 10.f);
    //DrawDebugLine(detectorActor->GetWorld(), baseRight, baseLeft, FColor::Yellow, false, -1.f, 0, 10.f);

    //Top of the "cacke"
    FVector topRight = downDetectionHeight + rightAngleVector * maxConeDistance;
    FVector topLeft = downDetectionHeight + leftAngleVector * maxConeDistance;
    DrawDebugLine(detectorActor->GetWorld(), downDetectionHeight, topRight, FColor::Yellow, false, -1.f, 0, 10.f);
    DrawDebugLine(detectorActor->GetWorld(), downDetectionHeight,topLeft, FColor::Yellow, false, -1.f, 0, 10.f);
    //DrawDebugLine(detectorActor->GetWorld(), topRight,topLeft, FColor::Yellow, false, -1.f, 0, 10.f);


//     //veritcal Lines
//     DrawDebugLine(detectorActor->GetWorld(), topRight, baseRight, FColor::Yellow, false, -1.f, 0, 10.f);
//     DrawDebugLine(detectorActor->GetWorld(), topLeft, baseLeft, FColor::Yellow, false, -1.f, 0, 10.f);
//     DrawDebugLine(detectorActor->GetWorld(), topDetectionHeigth, downDetectionHeight, FColor::Yellow, false, -1.f, 0, 10.f);
}

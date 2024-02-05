// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_CheckInCone.h"
#include "Game/HIGameData.h"

UHITask_CheckInCone::UHITask_CheckInCone()
{

}

UHITask_CheckInCone* UHITask_CheckInCone::HICheckInCone(UGameplayAbility* OwningAbility, TArray<AHIAbilityCharacter*>_charactersToCheck, float _lenght, float _coneAngle, FVector _emitterPos, FVector _coneDirection)
{
    UHITask_CheckInCone* MyObj = NewAbilityTask<UHITask_CheckInCone>(OwningAbility);
    MyObj->abilityCharactersToCheck = _charactersToCheck;
    MyObj->lenght = _lenght;
    MyObj->coneAngle = _coneAngle;
    MyObj->emitterPos = _emitterPos;
    MyObj->coneDirection = _coneDirection;
    return MyObj;
}

void UHITask_CheckInCone::Activate()
{
    Super::Activate();

    abilityCharactersInCone.Empty();
    AHIAbilityCharacter* owner = Cast<AHIAbilityCharacter>(GetAvatarActor());
    for (AHIAbilityCharacter* it : abilityCharactersToCheck)
    {
        if (!((it) == owner))
        {
            FVector itLocation;
            itLocation = it->GetActorLocation();
            FVector distToEmitter = itLocation - emitterPos;

            if (distToEmitter.Size() <= lenght)
            {
                distToEmitter.Normalize();
                float dotProduct = FVector::DotProduct(coneDirection, distToEmitter);
                float angleToConeDirection = FMath::RadiansToDegrees(FMath::Acos(dotProduct));
                if (angleToConeDirection < coneAngle)
                {
                    FHitResult hit;
                    FCollisionQueryParams params;
                    params.AddIgnoredActor(owner);
                    if (UHIGameData::HIGetWerewolfWorld()->LineTraceSingleByChannel(hit, owner->GetActorLocation(), it->GetActorLocation(), ECC_Visibility, params))
                    {
                        AActor* hittedActor = hit.GetActor();
                        if (it == hittedActor)
                        {
                            abilityCharactersInCone.Add(it);
                        }
                    }
                }
                else
                {
                    float capsuleRadius = it->GetCapsuleComponent()->GetScaledCapsuleRadius();
                    distToEmitter = itLocation - emitterPos;
                    FVector itDirectionToCenterCone = coneDirection * distToEmitter;
                    itDirectionToCenterCone = itDirectionToCenterCone - itLocation;
                    itDirectionToCenterCone.Normalize();
                    FVector radiusPos = itLocation + (itDirectionToCenterCone * capsuleRadius);
                    FVector distToEmitterRadius = radiusPos - emitterPos;
                    if (distToEmitterRadius.Size() <= lenght)
                    {
                        distToEmitterRadius.Normalize();
                        dotProduct = FVector::DotProduct(coneDirection, distToEmitterRadius);
                        angleToConeDirection = FMath::RadiansToDegrees(FMath::Acos(dotProduct));

                        if (angleToConeDirection < coneAngle)
                        {
                            FHitResult hit;
                            FCollisionQueryParams params;
                            params.AddIgnoredActor(owner);
                            if (UHIGameData::HIGetWerewolfWorld()->LineTraceSingleByChannel(hit, owner->GetActorLocation(), it->GetActorLocation(), ECC_Visibility, params))
                            {
                                AActor* hittedActor = hit.GetActor();
                                if (it == hittedActor)
                                {
                                    abilityCharactersInCone.Add(it);
                                }
                            }
                        }
                        else
                        {

                        }
                    }
                }
            }
            else
            {

            }
        }
    }

    if (abilityCharactersInCone.Num() >= 1)
    {
        onHit.Broadcast(abilityCharactersInCone);
    }
    else
    {
        noHit.Broadcast();
    }
    EndTask();
}

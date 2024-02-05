// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_SphereRadius.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
UHITask_SphereRadius::UHITask_SphereRadius()
{

}

UHITask_SphereRadius* UHITask_SphereRadius::HICreateSphere(UGameplayAbility* OwningAbility, float _radius, FVector _pos, ECollisionChannel _collisionChannel, bool _drawDebug)
{
    UHITask_SphereRadius* MyObj = NewAbilityTask<UHITask_SphereRadius>(OwningAbility);
    MyObj->pos = _pos;
    MyObj->radius = _radius;
    MyObj->collisionChannel = _collisionChannel;
    MyObj->drawSphere = _drawDebug;
    return MyObj;
}

void UHITask_SphereRadius::Activate()
{
    CollideSphere();
    EndTask();

}

void UHITask_SphereRadius::CollideSphere()
{
    TArray<FHitResult> hitResults;

    TArray<AActor*> HitActors;

    if (GetWorld()->SweepMultiByChannel(hitResults, pos, pos, FQuat::Identity, collisionChannel, FCollisionShape::MakeSphere(radius)))
    {
        for (FHitResult Iter : hitResults)
        {
            HitActors.Add(Iter.GetActor());
        }



        if (drawSphere)
        {
            DrawDebugSphere(GetWorld(), pos, radius, 64.f, FColor::Red, false, 2.f);
        }

        hit.Broadcast(HitActors,hitResults);
        return;

    }
    else if (drawSphere)
    {
        DrawDebugSphere(GetWorld(), pos, radius, 64.f, FColor::Green, false, 2.f);
        noHit.Broadcast();
        return;
    }

}

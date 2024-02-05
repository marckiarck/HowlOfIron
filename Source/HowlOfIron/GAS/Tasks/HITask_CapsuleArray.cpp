// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_CapsuleArray.h"

UHITask_CapsuleArray::UHITask_CapsuleArray()
{

}

UHITask_CapsuleArray* UHITask_CapsuleArray::HICreateCapsule(UGameplayAbility* OwningAbility, FVector _pos, float _height, float _radius, FRotator _rotation, bool _drawDebug)
{
    UHITask_CapsuleArray* MyObj = NewAbilityTask<UHITask_CapsuleArray>(OwningAbility);

    MyObj->pos = _pos;
    MyObj->radius = _radius;
    MyObj->height = _height;
    MyObj->rotation = _rotation;
    MyObj->drawDebug = _drawDebug;
    
    return MyObj;
}

void UHITask_CapsuleArray::Activate()
{
    HICollideCapsule();
    EndTask();
}

void UHITask_CapsuleArray::HICollideCapsule()
{
    TArray<FHitResult> hitResults;
    TArray<AActor*> HitActors;

   
   rotation += GetAvatarActor()->GetActorRotation();
    FQuat quat = rotation.Quaternion();



    if (GetWorld()->SweepMultiByChannel(hitResults, pos, pos, quat, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeCapsule(radius, height)))
    {
        for (FHitResult Iter : hitResults)
        {
            HitActors.Add(Iter.GetActor());
        }

        if (drawDebug)
        {
            DrawDebugCapsule(GetWorld(), pos, height, radius, quat, FColor::Red, false, 2.f);
        }

        hit.Broadcast(HitActors,hitResults);
        return;
    }
    else if (drawDebug)
    {
        DrawDebugCapsule(GetWorld(), pos, height, radius, quat, FColor::Green, false, 2.f);
        noHit.Broadcast();
        return;
    }
}

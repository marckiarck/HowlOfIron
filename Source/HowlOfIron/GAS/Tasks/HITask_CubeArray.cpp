// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_CubeArray.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"


UHITask_CubeArray::UHITask_CubeArray()
{

}


UHITask_CubeArray* UHITask_CubeArray::HICreateCube(UGameplayAbility* OwningAbility, FVector _size, FVector _pos, bool _drawDebug)
{
    UHITask_CubeArray* MyObj = NewAbilityTask<UHITask_CubeArray>(OwningAbility);
    MyObj->pos = _pos;
    MyObj->size = _size;
    MyObj->drawDebug = _drawDebug;
    return MyObj;
}

void UHITask_CubeArray::Activate()
{
    HICollideCube();
    EndTask();
}

void UHITask_CubeArray::HICollideCube()
{
    TArray<FHitResult> hitResults;
    TArray<AActor*> HitActors;




    if (GetWorld()->SweepMultiByChannel(hitResults, pos, pos+0.0001f, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeBox(size)))
    {
        for (FHitResult Iter : hitResults)
        {
            HitActors.Add(Iter.GetActor());
        }



        if (drawDebug)
        {
            DrawDebugBox(GetWorld(),pos,size,FQuat::Identity,FColor::Red,false,2.f);        
        }

        hit.Broadcast(HitActors,hitResults);
        return;

    }
    else if (drawDebug)
    {
        DrawDebugBox(GetWorld(), pos, size, FQuat::Identity, FColor::Green, false, 2.f);
        noHit.Broadcast();
        return;
    }

}
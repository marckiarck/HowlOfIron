// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_RaycastHit.h"
#include "Game/HIGameData.h"

UHITask_RaycastHit::UHITask_RaycastHit()
{

}

UHITask_RaycastHit* UHITask_RaycastHit::HIShootRaycast(UGameplayAbility* OwningAbility, float _waitraycast, FVector _locationToShot, TEnumAsByte<ECollisionChannel> _CollisionChannel)
{
    UHITask_RaycastHit* MyObj = NewAbilityTask<UHITask_RaycastHit>(OwningAbility);
    MyObj->locationToShoot = _locationToShot;
    MyObj->typeCollsion = _CollisionChannel;
    return MyObj;
}

void UHITask_RaycastHit::Activate()
{
    Shoot(locationToShoot);
    EndTask();
}

void UHITask_RaycastHit::Shoot(FVector _locationToShot)
{
    AActor* owner = AbilitySystemComponent->GetAvatarActor();
    ACharacter* player = GetWorld()->GetFirstPlayerController()->GetCharacter();
    FCollisionQueryParams params;
    params.AddIgnoredActor(owner);

    FHitResult hit;

    if (GetWorld()->LineTraceSingleByChannel(hit, owner->GetActorLocation(), _locationToShot,typeCollsion, params))
    {
        if (UHIGameData::HIGetDebugMode())
        {
            DrawDebugLine(GetWorld(), owner->GetActorLocation(), hit.GetActor()->GetActorLocation(), FColor::Red, false, 2.f);
        }

        onHit.Broadcast(hit.GetActor(), hit);
    }
    else
    {
        if (UHIGameData::HIGetDebugMode())
        {
            DrawDebugLine(GetWorld(), owner->GetActorLocation(), _locationToShot, FColor::Green, false, 2.f);
        }
        noHit.Broadcast(nullptr, hit);
    }

}

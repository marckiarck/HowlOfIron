// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_SpawnNiagaraWhileAbility.h"
#include "NiagaraSystem.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

UHITask_SpawnNiagaraWhileAbility* UHITask_SpawnNiagaraWhileAbility::HISpawnAttachedNiagaraSystem(UGameplayAbility* OwningAbility, UNiagaraSystem* _niagaraSystem, USceneComponent* _ComponentToAttach, FName _SocketName, FVector _locationOffset, FRotator _Rotator, FVector _scale, EAttachLocation::Type _locationType, bool _autoDestroy, ENCPoolMethod _poolMethod)
{

    UHITask_SpawnNiagaraWhileAbility* returnedTask = NewAbilityTask<UHITask_SpawnNiagaraWhileAbility>(OwningAbility);

    returnedTask->niagaraSystem = _niagaraSystem;
    returnedTask->ComponentToAttach = _ComponentToAttach;
    returnedTask->SocketName = _SocketName;
    returnedTask->locationOffset = _locationOffset;
    returnedTask->RotatorOffset = _Rotator;

    if (_scale.Size() <= 0.2f)
    {
        returnedTask->ScaleOffset = FVector(1.f);
    }
    else
    {
        returnedTask->ScaleOffset = _scale;
    }

    returnedTask->locationType = _locationType;
    returnedTask->autodestroy = _autoDestroy;
    returnedTask->poolMethod = _poolMethod;

    return returnedTask;
}

UHITask_SpawnNiagaraWhileAbility* UHITask_SpawnNiagaraWhileAbility::HISpawnNiagaraSystemAtLocation(UGameplayAbility* OwningAbility, UNiagaraSystem* _niagaraSystem, FVector _locationOffset)
{

    UHITask_SpawnNiagaraWhileAbility* returnedTask = NewAbilityTask<UHITask_SpawnNiagaraWhileAbility>(OwningAbility);

    returnedTask->niagaraSystem = _niagaraSystem;
    returnedTask->locationOffset = _locationOffset;

    return returnedTask;

}

void UHITask_SpawnNiagaraWhileAbility::Activate()
{
    if (niagaraSystem)
    {
        if (ComponentToAttach)
        {
            niagaraParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(niagaraSystem, ComponentToAttach, SocketName, locationOffset, RotatorOffset, ScaleOffset, locationType, autodestroy, poolMethod);
        }
        else
        {
            niagaraParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetAvatarActor()->GetWorld(), niagaraSystem, locationOffset);
        }
    }
}

void UHITask_SpawnNiagaraWhileAbility::OnDestroy(bool bInOwnerFinished)
{

    if (niagaraParticleComponent)
    {
        //niagaraParticleComponent->DestroyInstance();
        niagaraParticleComponent->DestroyComponent();
    }

    Super::OnDestroy(bInOwnerFinished);
}

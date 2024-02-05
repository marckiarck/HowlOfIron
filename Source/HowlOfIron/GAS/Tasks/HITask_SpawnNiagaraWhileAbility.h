// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Engine/EngineTypes.h"
#include "HITask_SpawnNiagaraWhileAbility.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHITask_SpawnNiagaraWhileAbility : public UAbilityTask
{
    GENERATED_BODY()



public:

protected:

private:

    UPROPERTY(Transient)
       class UNiagaraSystem* niagaraSystem;

    UPROPERTY(Transient)
       class USceneComponent* ComponentToAttach;

    UPROPERTY()
        FName SocketName;

    UPROPERTY()
        FVector locationOffset;

    UPROPERTY()
        FRotator RotatorOffset;

    UPROPERTY()
        FVector ScaleOffset;

    UPROPERTY()
    TEnumAsByte<EAttachLocation::Type> locationType;
    //    EAttachLocation::Type locationType;

    UPROPERTY()
        bool autodestroy;

    UPROPERTY()
        ENCPoolMethod poolMethod;


    UPROPERTY(Transient)
       class UNiagaraComponent* niagaraParticleComponent;

public:

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UHITask_SpawnNiagaraWhileAbility* HISpawnAttachedNiagaraSystem(UGameplayAbility* OwningAbility, UNiagaraSystem* _niagaraSystem, USceneComponent* _ComponentToAttach, FName _SocketName, FVector _locationOffset, FRotator _Rotator, FVector _scale, EAttachLocation::Type _locationType, bool _autoDestroy, ENCPoolMethod _poolMethod);


    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UHITask_SpawnNiagaraWhileAbility* HISpawnNiagaraSystemAtLocation(UGameplayAbility* OwningAbility, UNiagaraSystem* _niagaraSystem, FVector _locationOffset);

protected:

private:

    virtual void Activate() override;
    virtual void OnDestroy(bool bInOwnerFinished) override;

};

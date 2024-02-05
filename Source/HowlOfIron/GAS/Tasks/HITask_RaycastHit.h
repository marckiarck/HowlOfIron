// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HITask_RaycastHit.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRaycastShoot, const AActor*, ActorHitRaycast, const FHitResult, HitResultRaycast);


UCLASS()
class HOWLOFIRON_API UHITask_RaycastHit : public UAbilityTask
{
    GENERATED_BODY()


public:

UHITask_RaycastHit();

public:

    UPROPERTY(BlueprintAssignable)
        FRaycastShoot onHit;

    UPROPERTY(BlueprintAssignable)
        FRaycastShoot noHit;

    UPROPERTY()
        FVector locationToShoot;

    TEnumAsByte<ECollisionChannel> typeCollsion;

protected:


private:


public:

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
    static UHITask_RaycastHit* HIShootRaycast(UGameplayAbility* OwningAbility, float _waitraycast, FVector _locationToShot, TEnumAsByte<ECollisionChannel> _CollisionChannel);

protected:


private:

    virtual void Activate() override;
    void Shoot(FVector _locationToShot);


};

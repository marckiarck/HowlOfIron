// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "UObject/ObjectMacros.h"
#include "HITask_CapsuleArray.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCapsuleArrayDelegate, const TArray<AActor*>&, ActorsArray, const TArray<FHitResult>&, HitResutlsArray);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCapsuleEndDelegate);



UCLASS()
class HOWLOFIRON_API UHITask_CapsuleArray : public UAbilityTask
{
    GENERATED_BODY()

public:

    UHITask_CapsuleArray();

public:

    UPROPERTY(BlueprintAssignable)
        FCapsuleArrayDelegate hit;
    UPROPERTY(BlueprintAssignable)
        FCapsuleEndDelegate noHit;

protected:

private:

    FVector pos;
    float radius;
    float height;
    FRotator rotation;
    bool drawDebug;


public:

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UHITask_CapsuleArray* HICreateCapsule(UGameplayAbility* OwningAbility,  FVector _pos,float _height,float _radius,FRotator _rotation, bool _drawDebug);


protected:

private:

    virtual void Activate() override;
    void HICollideCapsule();

};

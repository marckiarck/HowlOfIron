// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Game/DataTable/FHIWerewolfSound.h"
#include "HIDetectionSound.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIDetectionSound : public UAnimNotify
{
    GENERATED_BODY()


public:

protected:

private:

    UPROPERTY(EditAnywhere, meta = (RequiredAssetDataTags = "RowStructure=HIWerewolfSound"))
        UDataTable* ValueDatatable;

    UPROPERTY(EditAnywhere)
        FName rowName;



    UPROPERTY()
        float radius = 2000.f;
    UPROPERTY()
        float force = 30.f;

        UPROPERTY()
    float changeradius;

    UPROPERTY()    
        float percentDiscountLowSteam = 0.3f;

    UPROPERTY()
        float percentDiscountHighSteam = 1.f;

    UPROPERTY()
        float minumValue;



public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

protected:

private:


};

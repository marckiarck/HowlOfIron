// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Engine/DataTable.h"
#include "HIPlaySound.generated.h"

/**
 *
 */
 UENUM()
     enum typeSound
 {
     Sound2D UMETA(DisplayName = "Sound2D"),
     Sound3D UMETA(DisplayName = "Sound3D"),
 };

 



UCLASS()
class HOWLOFIRON_API UHIPlaySound : public UAnimNotify
{
    GENERATED_BODY()


public:

public:

protected:

private:


    UPROPERTY(EditAnywhere)
        TEnumAsByte<typeSound> soundenum;

    UPROPERTY(EditAnywhere, meta = (RequiredAssetDataTags = "RowStructure=HIAudioStruct"))
        UDataTable* SoundDataTable;

    UPROPERTY(EditAnywhere)
        FName rowNameSound;

public:

    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

protected:

private:

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AnimNotifies/HIPlaySound.h"
#include "Game/Audio/HIAudioStruct.h"

void UHIPlaySound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

    if (!SoundDataTable)
    {
        return;
    }

    FDataTableRowHandle structSound;

    structSound.DataTable = SoundDataTable;
    structSound.RowName = rowNameSound;

    AActor* owner = MeshComp->GetOwner();

    switch (soundenum)
    {
        case typeSound::Sound2D:
        {
            UHIAudio::HIUseSound2D(owner,structSound);
        }
        break;

        case typeSound::Sound3D:
        {
            UHIAudio::HIUseSound3D(owner,owner->GetActorLocation(),structSound);
        }
        break;

        default:
        {
            return;
        }
    }
}

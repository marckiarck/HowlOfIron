// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Audio/HIAmbientSound.h"
#include "Components/AudioComponent.h"
#include "Game/HIGameData.h"
#include "HIAudioStruct.h"

AHIAmbientSound::AHIAmbientSound()
{

    UHIGameData::HISetSpeaker(this);

    combatMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("CombatMusicComponent"));
    huntMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("HuntMusicComponent"));
    pauseMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PauseMusicComponent"));
}

void AHIAmbientSound::HISetHuntMusic(FDataTableRowHandle _huntMusic)
{
    huntMusic = _huntMusic;
}

void AHIAmbientSound::HISetCombatMusic(FDataTableRowHandle _combatMusic)
{
    combatMusic = _combatMusic;
}

void AHIAmbientSound::HISetPausetMusic(FDataTableRowHandle _pauseMusic)
{
    pauseMusic = _pauseMusic;
}

void AHIAmbientSound::HIPlayMusic(MusicType _musicType, FDataTableRowHandle _Music, float _durationFadeIn, float _volumeMultiplier /*= 1.f*/, float _StartTime, EAudioFaderCurve _FadeInType)
{

    FString ContextString = TEXT("Data table context");
    FHIAudioStruct* Row = nullptr;
    Row = _Music.DataTable->FindRow<FHIAudioStruct>(_Music.RowName, ContextString, true);

    UAudioComponent* tempAudioComponent = nullptr;

    switch (_musicType)
    {
    case MusicType::CombatMusic:
    {

        tempAudioComponent = combatMusicComponent;
    }
    break;

    case MusicType::HuntMusic:
    {
        tempAudioComponent = huntMusicComponent;
    }
    break;

    case MusicType::PauseMusic:
    {
        tempAudioComponent = pauseMusicComponent;
    }
    break;

    default:
        break;

    }

    if (tempAudioComponent)
    {
        actualComponent = tempAudioComponent;
        tempAudioComponent->SetSound(Row->sound);
        tempAudioComponent->SetVolumeMultiplier(Row->volume);
        tempAudioComponent->SetPitchMultiplier(Row->pitch);
        tempAudioComponent->FadeIn(_durationFadeIn, _volumeMultiplier, _StartTime, _FadeInType);
    }

}



void AHIAmbientSound::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    HIStartMusics();
}

void AHIAmbientSound::BeginPlay()
{

    Super::BeginPlay();

    actualComponent = huntMusicComponent;

}

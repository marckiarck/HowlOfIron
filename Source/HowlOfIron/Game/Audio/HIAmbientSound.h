// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/AmbientSound.h"
#include "Engine/DataTable.h"
#include "Components/AudioComponent.h"

#include "HIAmbientSound.generated.h"

/**
 *
 */



UENUM()
enum MusicType
{
    HuntMusic,
    CombatMusic,
    PauseMusic
   
};



UCLASS()
class HOWLOFIRON_API AHIAmbientSound : public AActor
{
    GENERATED_BODY()

public:

    AHIAmbientSound();

public:

    UPROPERTY(BlueprintReadOnly)
        FDataTableRowHandle huntMusic;
    UPROPERTY(BlueprintReadOnly)
        FDataTableRowHandle combatMusic;
    UPROPERTY(BlueprintReadOnly)
        FDataTableRowHandle pauseMusic;


    UPROPERTY(EditAnywhere)
        UAudioComponent* huntMusicComponent;

    UPROPERTY(EditAnywhere)
        UAudioComponent* combatMusicComponent;

    UPROPERTY(EditAnywhere)
        UAudioComponent* pauseMusicComponent;



    UPROPERTY(BlueprintReadWrite)
        UAudioComponent* actualComponent;


protected:

private:

public:

    UFUNCTION(BlueprintCallable, meta = (HidePin = "Target")/* (HidePin = "Target", DefaultToSelf = "Target")*/)
        void HISetHuntMusic(FDataTableRowHandle _huntMusic);
    UFUNCTION(BlueprintCallable)
        void HISetCombatMusic(FDataTableRowHandle _combatMusic);
    UFUNCTION(BlueprintCallable)
        void HISetPausetMusic(FDataTableRowHandle _pauseMusic);


    UFUNCTION(BlueprintCallable)
        void HIPlayMusic(MusicType _musicType, FDataTableRowHandle _Music, float _durationFadeIn, float _volumeMultiplier = 1.f, float _StartTime = 0.f, EAudioFaderCurve _FadeInType = EAudioFaderCurve::Linear);


    UFUNCTION(BlueprintImplementableEvent)
        void HIPlayCombat();


    UFUNCTION(BlueprintImplementableEvent)
        void HIPlayHunt();


    UFUNCTION(BlueprintImplementableEvent)
        void HIPlayPause();


    UFUNCTION(BlueprintImplementableEvent)
        void HIStartMusics();



protected:

private:





    virtual void PostInitializeComponents() override;
    virtual void BeginPlay() override;



};

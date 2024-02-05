// Copyright Epic Games, Inc. All Rights Reserved.


#include "HowlOfIronGameModeBase.h"

#include "Characters/VincentVolk/HIWerewolfController.h"
#include "Characters/VincentVolk/HIWerewolf.h"
#include "Audio/HIAmbientSound.h"



AHowlOfIronGameModeBase::AHowlOfIronGameModeBase()
{

    DefaultPawnClass = AHIWerewolf::StaticClass();
    PlayerControllerClass = AHIWerewolfController::StaticClass();

}

void AHowlOfIronGameModeBase::StartPlay()
{

    Super::StartPlay();

    TArray<AActor*> ambientSoundsActors;
    UWorld* puntero = GetWorld();
    UGameplayStatics::GetAllActorsOfClass(puntero, speakerclass, ambientSoundsActors);

    if (ambientSoundsActors.Num() == 0)
    {
        GetWorld()->SpawnActor(speakerclass);
    }
}

void AHowlOfIronGameModeBase::StartToLeaveMap()
{
    Super::StartToLeaveMap();

    AHIObjectPooler_Actors::HIResetObjectPooler();
    AHIConditionRegister::HIResetConditionRegister();
}

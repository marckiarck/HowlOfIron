// @AUTHOR: Guillermo Suárez

#include "MapLogic/HISteamTrigger.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Game/HIGameData.h"


AHISteamTrigger::AHISteamTrigger(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.DoNotCreateDefaultSubobject(FName("Sprite")))
{
    PrimaryActorTick.bCanEverTick = true;
}

void AHISteamTrigger::BeginPlay()
{

    Super::BeginPlay();

    HIActivateSteam(timeActivated);
}


void AHISteamTrigger::HIEnemiesLostVision()
{
    TArray<AHIEnemy*> enemies = UHIGameData::HIGetEnemiesArray();

    for (AHIEnemy* itEnem : enemies)
    {
        itEnem->HISetNormalDetection();
    }
}

void AHISteamTrigger::HIActivateSteam(float _time)
{

    isActive = true;
    elapsedActived = _time;
    GetCollisionComponent()->SetCollisionResponseToChannel(GAME_TRACE_STEAM, ECollisionResponse::ECR_Block);
#if WITH_EDITOR
    GetCollisionComponent()->ShapeColor = FColor::Silver;
#endif
    HIActivationChange();

}

void AHISteamTrigger::HIDeactivateSteam()
{

    isActive = false;
    HIDeactivationChange();
    GetCollisionComponent()->SetCollisionResponseToChannel(GAME_TRACE_STEAM, ECollisionResponse::ECR_Ignore);
#if WITH_EDITOR
    GetCollisionComponent()->ShapeColor = FColor::Red;
#endif
    elapsedActived = 0.f;

    if (cycle)
    {
        elapsedDeactivated = timeDeactivated;
    }
}

void AHISteamTrigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (isActive && cycle)
    {
        elapsedActived -= DeltaTime;

        if (elapsedActived <= 0.f)
        {
            HIDeactivateSteam();
        }
    }
    if (!isActive && cycle)
    {
        elapsedDeactivated -= DeltaTime;

        if (elapsedDeactivated <= 0.f)
        {
            HIActivateSteam(timeActivated);
        }
    }

}

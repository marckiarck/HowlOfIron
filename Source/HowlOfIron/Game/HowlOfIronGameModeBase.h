// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HowlOfIronGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API AHowlOfIronGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

        AHowlOfIronGameModeBase();

public:

    UPROPERTY(EditAnywhere)
        TSubclassOf<AHIAmbientSound> speakerclass;


protected:

private:


public:

    virtual void StartPlay() override;

    virtual void StartToLeaveMap() override;

protected:

private:

};

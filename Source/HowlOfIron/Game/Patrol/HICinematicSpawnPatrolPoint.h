/*
* Don't inherit from this class. IT has being created for a very specific purpouse.
*/

#pragma once
#include "CoreMinimal.h"
#include "Game/Patrol/HISpawnPatrolPoint.h"
#include "HICinematicSpawnPatrolPoint.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API AHICinematicSpawnPatrolPoint : public AHISpawnPatrolPoint
{
    GENERATED_BODY()


public:
    virtual void BeginPlay() override;
    UFUNCTION(BlueprintCallable)
        TArray<UHICondition*> HIGetConditionPoints();

    UFUNCTION(BlueprintImplementableEvent)
    void InitializeCinematicPoint();

private:
    UFUNCTION()
        void HIEnableEnemy();
};

// @AUTHOR: Guillermo Suárez
#pragma once

#if WITH_GAMEPLAY_DEBUGGER

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class AActor;

class HOWLOFIRON_API FGDEnemyCategory : public FGameplayDebuggerCategory
{

public:
    FGDEnemyCategory();

public:


protected:
    struct FAbilitySys
    {
        FString actorName;
        FString maxHealth;
        FString health;
        FString maxFear;
        FString fear;
        FString speed;

        FString detectionValue;

        FString distanceTo;
        void Serialize(FArchive& Ar);
    } DataPack;

private:


public:
    void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
    void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

    static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

protected:


private:


};
#endif // WITH_GAMEPLAY_DEBUGGER
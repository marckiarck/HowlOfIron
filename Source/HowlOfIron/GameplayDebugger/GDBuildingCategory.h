// @AUTHOR: Carlos Fernández
#pragma once

#if WITH_GAMEPLAY_DEBUGGER

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class AActor;

class HOWLOFIRON_API FGDBuildingCategory : public FGameplayDebuggerCategory
{

public:
    FGDBuildingCategory();

public:


protected:
    struct FBuildingParams
    {
        FString actorName;
        FString distanceToWerewolf;
        FString height;
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
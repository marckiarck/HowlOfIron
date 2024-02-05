// @AUTHORS: Guillermo Suárez, Marco Fernández

#pragma once

#if WITH_GAMEPLAY_DEBUGGER

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class HIWerewolf;
class AActor;

class HOWLOFIRON_API FGDAbilitiesCategory : public FGameplayDebuggerCategory
{
public:
    FGDAbilitiesCategory();

public:


protected:
    struct FAbilitySys
    {
        FString actorName;
        FString maxHealth;
        FString health;
        FString armour;
        FString speed;
        FString run;
        FString howl;
        FString rage;
        FString damage1;
        FString damage2;
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
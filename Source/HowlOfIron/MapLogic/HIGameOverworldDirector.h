// created by pablo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "MapLogic/HI_Requisit.h"
#include "UI/HILoadScreenHUD.h"
#include "HIGameOverworldDirector.generated.h"


UCLASS(Blueprintable, BlueprintType)
class HOWLOFIRON_API UHIGameOverworldDirector : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        UHIMission* actualMission = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<UObject*> cinematics;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString levelToLoad;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UHILoadScreenHUD* loadScreenWidget = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool levelPrepared = false;

public:

    UHIGameOverworldDirector() = default;
    ~UHIGameOverworldDirector() { UE_LOG(LogTemp, Log, TEXT("GOD script deleted.")) };

    UFUNCTION(BlueprintCallable)
        void CompletedRequisitMission(MissionReq _reqEnum);

    UFUNCTION(BlueprintCallable)
        void SetMission(UHIMission* _mission);

    UFUNCTION(BlueprintCallable)
        void ShowMission();

    UFUNCTION(BlueprintCallable)
        virtual void ExecuteReq(int i);

    UFUNCTION()
        void OnLevelLoaded();

    UFUNCTION()
        void OnLevelUnloaded();

    UFUNCTION(BlueprintCallable)
        void HideLoadScreen();
private:
    UFUNCTION()
        void ResetMission();

    UFUNCTION()
        void Endmission();

    UFUNCTION()
        void StartCinematic();

    UFUNCTION()
        void EndCinematic();
};

// Created by pablo

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "../Characters/VincentVolk/HIWerewolf.h"
#include "../Characters/Enemies/HIEnemy.h"
#include "HICameraManager.generated.h"


UENUM(BlueprintType)
enum class CameraView : uint8
{
    HUNT = 0 UMETA(DisplayName = "HUNT"),
    COMBAT = 1  UMETA(DisplayName = "COMBAT"),
    SCRIPTED = 2     UMETA(DisplayName = "SCRIPTED"),
};


USTRUCT(Blueprintable, BlueprintType)
struct FHI_DT_Camera : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float distanceFromPlayer = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float height = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float leftDeviation = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        FRotator rotation;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float interpolationSpeed = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        UCurveFloat* lerpCurve = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float maxTopInclination = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float maxBottomInclination = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float distFindTarget = 1300;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float distLoseTarget = 2000;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float changeTargetDelay = 0.25f;

};

UCLASS()
class HOWLOFIRON_API AHICameraManager : public APlayerCameraManager
{
    GENERATED_BODY()
public:
    AHICameraManager();
    ~AHICameraManager();

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        AHIWerewolf* player;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        CameraView currentCamView;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UDataTable* datatable;

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
        float distanceFromPlayer;

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
        float height;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float leftDeviation;

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
        FRotator rotation;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float interpolationSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        UCurveFloat* lerpCurve;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        float maxTopInclination;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        float maxBottomInclination;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float distFindTarget;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float distLoseTarget;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float changeTargetDelay;

    UPROPERTY()
        bool changingMode = false;

    UPROPERTY(BlueprintReadWrite)
        bool centeredCamera = true;

    UPROPERTY()
        bool targetMode = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        AHIEnemy* targetedActor;

    UPROPERTY()
        FVector camPos;

    UPROPERTY()
        float postCombatTimer = 0;

    UPROPERTY()
        float changetargetDelayTimer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        bool changeTargetAllowed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool buleanoWarro = false;

    UPROPERTY(Transient)
        AActor* targetSnapped = nullptr;

    UPROPERTY(Transient)
        UWorld* hiWorld;

    UPROPERTY()
        FRotator camInitRot;

    UPROPERTY()
        FVector springArmSocInitRot;

    UPROPERTY()
        float springArmLengInitRot;

    UPROPERTY()
        float interpAlpha = 0.f;

    UPROPERTY()
        float timerSnap = 0.f;

    UPROPERTY()
        float timerToCenterCamera = 0.f;

    float camDist = 0;
protected:


private:
    FHI_DT_Camera* Row = nullptr;
    AHIWerewolfController* werewolfController;

public:
    UFUNCTION(BlueprintCallable)
        void ChangeCameraView(CameraView _view);

    UFUNCTION(BlueprintCallable)
        void TargetChange(bool _rightSide);

    UFUNCTION(BlueprintCallable)
        void TargetDetection();

    UFUNCTION(BlueprintCallable)
        void TargetEmpty();

    UFUNCTION(BlueprintCallable)
        void CentrateCamera(float DeltaTime);

    UFUNCTION()
        void TargetSnapped(float DeltaTime);

    UFUNCTION(BlueprintCallable)
        void HICenterCameraExecution(FRotator _targetRotation);

    UFUNCTION(BlueprintCallable)
        void HIBlockCameraInputRotation(bool _isBlocked);

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

private:

    UFUNCTION()
        void CameraMode(float DeltaTime);

    UFUNCTION()
        void TargetOn(float DeltaTime);

    UFUNCTION()
        void TargetOff();

    UFUNCTION()
        void HIInitVars(int _value);

    UFUNCTION()
        void HIScriptedCameraView();

    UFUNCTION()
        void HISweepActors(TArray<FHitResult>& _hitResult, ECollisionChannel _collisionChannel = ECollisionChannel::ECC_GameTraceChannel2);

};

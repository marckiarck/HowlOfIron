// @AUTHORS: Marco Fern�ndez, Guillermo Su�rez

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/HIVincentHUD.h"
#include "Game/HICameraManager.h"
#include <UI/Tooltips/HITooltipWidget.h>
#include "HIWerewolfController.generated.h"

/**
 *
 */

class AHIWerewolf;
class UHIPauseMenu;
class UHIGameInstance;

UCLASS()
class HOWLOFIRON_API AHIWerewolfController : public APlayerController
{
    GENERATED_BODY()

public:
    AHIWerewolfController();
    ~AHIWerewolfController();

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraSettings")
        float BaseTurnRate = 100.f;


    //     UPROPERTY(BlueprintReadOnly, Category = "GASDocumentation|UI")
    //         UHIVincentHUD* widgetref;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserInterface | PauseMenu")
        TSubclassOf<UHIPauseMenu> pauseMenuRef;

    FVector movementImput;


protected:

private:
    UPROPERTY(Transient)
        AHIWerewolf* werewolfOwner;

    UPROPERTY(Transient)
        AHICameraManager* camMana;

    UPROPERTY(Transient)
        UHIPauseMenu* pauseMenu;

    UPROPERTY(Transient)
        UHIGameInstance* gameInstance;

    UPROPERTY(Transient)
        UHITooltipWidget* tooltipWidget;

    UPROPERTY(EditAnywhere)
        TSubclassOf<UHITooltipWidget> TooltipWidgetClass;

    float camDeviation = 0;

    float deltaTime;

    float ownFPS;

public:
    virtual void BeginPlay() override;

    virtual void Tick(float _deltaSeconds) override;

    UFUNCTION(BlueprintCallable)
        void HIPauseMenuAction();

    UFUNCTION(BlueprintCallable)
        float HIGetFPS();

    UFUNCTION()
        AHIWerewolf* HIGetWerewolf();

protected:

private:

    void HIMoveForward(float _value);

    void HIMoveSide(float _value);

    void HICameraX(float _value);

    void HICameraY(float _value);

    void HIDash();

    void HILightAttack();

    void HIHeavyAttack();

    UFUNCTION(BlueprintCallable)
        void HIJump();

    void HIHowl();

    void HIFinisher();

    void HITarget();

    void HIDebugMode();

    void HIResetLevel();

    // Teleport cheat
    void HITeleportCheat();
    void HITeleportDown(float _value);
    void HITeleportUp(float _value);

    UFUNCTION()
        void HICalculateFPS(float _deltaTime);


};

// @AUTHORS: Guillermo Suárez, Marco Fernández
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/HITextClass.h"
#include <Components/CanvasPanel.h>
#include "HIVincentHUD.generated.h"

/**
 *
 */
class AHIWerewolf;

UCLASS()
class HOWLOFIRON_API UHIVincentHUD : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    
virtual void NativeConstruct() override;

public:
    AHIWerewolf* player;

    UPROPERTY(meta = (BindWidget))
        class UTextBlock* godMode;

    UPROPERTY(meta = (BindWidget))
        class UTextBlock* health;

    UPROPERTY(meta = (BindWidget))
        class UTextBlock* rage;

    UPROPERTY(meta = (BindWidget))
        class UTextBlock* showFPSText;

    UPROPERTY(meta = (BindWidget))
        class UCanvasPanel* debugBars;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UHITextClass* howlTextBlock;

    UPROPERTY(BlueprintReadOnly)
        float maxHealth;

    UPROPERTY(BlueprintReadOnly)
        float maxRage;

    UPROPERTY(BlueprintReadOnly)
        float fhealth;

    UPROPERTY(BlueprintReadOnly)
        float frage;

    UPROPERTY(BlueprintReadWrite)
        float howl;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        float progressHowl;

    UPROPERTY(BlueprintReadWrite)
        FString fMissionText;

    UPROPERTY(BlueprintReadOnly)
        FString fRequisitText;

    UPROPERTY(meta = (BindWidget))
        class UImage* arrow;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UHITextClass* missionText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UHITextClass* requisitesText;

protected:


private:



public:
    UFUNCTION()
        void HIInitVariables(const class UHIWerewolfAttributes* _attributes);

    UFUNCTION()
        void HIChangeHealth(float _health);

    UFUNCTION()
        void HIChangeHowlNum(float _howl);

    UFUNCTION()
        void HIChangeRage(float _rage);

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void HICalculateHealthBar();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void HICalculateRageBar();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void HIFadeInCutscene();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void HIEndCutscene();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void HIPlayEndAlpha();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HICalculateHowl();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HIFinishAlpha();

    UFUNCTION()
        void HISetMaxHealth(float _maxHealth);

    UFUNCTION()
        void HISetMaxRage(float _maxRage);

    UFUNCTION()
        void sethealth(float _health);

    UFUNCTION()
        void setrage(float _rage);

    UFUNCTION()
        void setMissiontext(FString _MissionText);

    UFUNCTION()
        void setRequisittext(FString _ReqText);

    UFUNCTION(BlueprintCallable)
        void SetGodMode(bool _godMode);

    UFUNCTION(BlueprintCallable)
        void HISetFPSVisibilityText(bool _validate);

    UFUNCTION()
        void HIUpdateFPSMessage(float _fps);

protected:



private:


};

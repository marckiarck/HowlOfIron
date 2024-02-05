// @AUTHORS: Guillermo Suárez
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HIMainMenu.generated.h"

class UHIButtonClass;
class UPanelWidget;
class AHIWerewolfController;
class UWidgetSwitcher;

UCLASS()
class HOWLOFIRON_API UHIMainMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
#pragma region MAIN_MENU
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UPanelWidget* mainButtonsPanel;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* playButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* continueButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* playgroundButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* levelSelectorButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* settingsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UHIButtonClass* creditsButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* exitButton;
#pragma endregion

#pragma region LEVEL_SELECTOR
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UPanelWidget* levelSelectorPanel;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* backLevelButton;
#pragma endregion

#pragma region SETTINGS
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UPanelWidget* settingsCanvas;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UWidgetSwitcher* settingsSwitcher;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* backSettingsButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* soundButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* graphicsButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* inputSettingsButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* uiButton;

#pragma endregion

protected:


private:
    int buttonsIndex;

public:

    UFUNCTION(BlueprintCallable)
        void HIPlayButton();

    UFUNCTION()
        void HIContinueButton();

    UFUNCTION()
        void HIPlaygroundButton();

    UFUNCTION()
        void HIBackLevelButton();

    UFUNCTION()
        void HIBackSettingsButton();

    UFUNCTION()
        void HILevelSelectorButton();

    UFUNCTION()
        void HISettingsButton();

	UFUNCTION()
		void HICreditsButton();

    UFUNCTION()
        void HIQuitGame();

    UFUNCTION()
        void HISoundButton();

    UFUNCTION()
        void HIGraphicsButton();

    UFUNCTION()
        void HIInputSettingsButton();

    UFUNCTION()
        void HIUIButton();

    UFUNCTION(BlueprintImplementableEvent)
        void HIOpenLevel();

    UFUNCTION(BlueprintImplementableEvent)
        void HIQuitGameEvent();

    UFUNCTION(BlueprintCallable)
        void HIUpdateButtonsIndex(int _operator);

    UFUNCTION(BlueprintCallable)
        void HIMenuNavigation();

    UFUNCTION(BlueprintPure)
        int HIGetButtonIndex();

    UFUNCTION(BlueprintImplementableEvent)
        void HISelectPlayButton();

    UFUNCTION(BlueprintImplementableEvent)
        void HIUnselectPlayButton();

    UFUNCTION(BlueprintImplementableEvent)
        void HISelectContinueButton();

    UFUNCTION(BlueprintImplementableEvent)
        void HIUnselectContinueButton();

    UFUNCTION(BlueprintImplementableEvent)
        void HISelectPlaygroundButton();

    UFUNCTION(BlueprintImplementableEvent)
        void HIUnselectPlaygroundButton();

	UFUNCTION(BlueprintImplementableEvent)
		void HISelectCreditsButton();

	UFUNCTION(BlueprintImplementableEvent)
		void HIUnselectCreditsButton();

    UFUNCTION(BlueprintImplementableEvent)
        void HISelectQuitButton();

    UFUNCTION(BlueprintImplementableEvent)
        void HIUnselectQuitButton();

    // virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

protected:


private:


};

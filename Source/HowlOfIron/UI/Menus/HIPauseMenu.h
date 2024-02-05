// @AUTHOR: Guillermo Suárez

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundClass.h"
#include "HIPauseMenu.generated.h"

class UHIButtonClass;
class UWidgetSwitcher;
class UHIRowClassSwitcher;
class UHIRowClassSlider;
class UHITextImageClass;
class AHIWerewolfController;
class UHIGameInstance;
class UGameUserSettings;
class UHIVincentHUD;

UCLASS()
class HOWLOFIRON_API UHIPauseMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:

#pragma region MAIN_BUTTONS
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHITextImageClass* settingsImage;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHITextImageClass* upgradesImage;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHITextImageClass* bindingsImage;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHITextImageClass* achievementsImage;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHITextImageClass* exitImage;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UWidgetSwitcher* widgSwitcher;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* leftButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* rightButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* applyButton;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        TArray<UHITextImageClass*> buttonsArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
        int arrayIndex;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
        int settingButtonsIndex;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float currentTranslation;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float minTranslation;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float maxTranslation;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int translationMultiplier;

#pragma endregion

#pragma region SETTING_BUTTONS
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* soundButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* graphicsButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* inputSettingsButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* uiButton;
#pragma endregion

#pragma region SETTING_SWITCHER
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UWidgetSwitcher* settingsSwitcher;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSwitcher* screenResolutionRow;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSwitcher* windowTypeRow;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSwitcher* brightnessRow;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSwitcher* qualityRow;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSlider* generalSoundSlider;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSlider* sfxSlider;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSlider* voicesSlider;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSlider* ambientSlider;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSwitcher* subtitlesSwitcher;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSwitcher* colorbindSwitcher;

#pragma endregion

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* quitButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIButtonClass* mainMenuButton;

#pragma region SOUND_MIXERS_AND_CLASSES
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundMix* generalSoundMix;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundClass* generalSoundClass;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundMix* sfxSoundMix;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundClass* sfxSoundClass;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundMix* voicesSoundMix;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundClass* voicesSoundClass;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundMix* ambientSoundMix;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundClass* ambientSoundClass;
#pragma endregion

#pragma region BINDINGS
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSlider* mouseSensivilitySlider;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSwitcher* reverseCameraSwitcher;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHIRowClassSwitcher* showFPSSwitcher;

#pragma endregion
protected:


private:
    UPROPERTY(Transient) AHIWerewolfController* controller;
    UPROPERTY(Transient) UHIGameInstance* gameInstance;
    UPROPERTY(Transient) UGameUserSettings* gameUserSettings;
    // UPROPERTY(Transient) TSubclassOf<UHIVincentHUD>  vincentHUD;
    UPROPERTY(Transient) UHIVincentHUD* vincentHUD;

    UPROPERTY() int screenResolutionIndex;
    UPROPERTY() int screenModeIndex;
    UPROPERTY() int quitButtonsIndex;
    UPROPERTY() int bindingsIndex;
    UPROPERTY() int soundSettingsIndex;
    UPROPERTY() int graphicSettingsIndex;
    UPROPERTY() int bindingSettingsIndex;
    UPROPERTY() int uiSettingsIndex;
    UPROPERTY() int reverseCameraIndex;
    UPROPERTY() int showFPSIndex;

public:
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

    UFUNCTION()
        int HIGetFPSIndex();

    UFUNCTION(BlueprintCallable)
        void HIRightSubMenuMovement();

    UFUNCTION(BlueprintCallable)
        void HILeftSubMenuMovement();

    UFUNCTION(BlueprintCallable)
        bool HIGoToSettings();

    UFUNCTION(BlueprintCallable)
        void HIInitRows();

    UFUNCTION()
        void HIInitVincentHUD();

#pragma region MAIN_MENU_SELECTION

    UFUNCTION(BlueprintNativeEvent)
        void HISelectedSettings();

    UFUNCTION(BlueprintNativeEvent)
        void HISelectedBindings();

    UFUNCTION(BlueprintNativeEvent)
        void HISelectedQuit();

    UFUNCTION(BlueprintNativeEvent)
        void HISelectedUpgrades();

    UFUNCTION(BlueprintNativeEvent)
        void HISelectedAchievments();

    UFUNCTION()
        void HIUpdateVisibilities();
#pragma endregion

    UFUNCTION()
        void HIUpdateSubmenuVisibility();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HISelectSound();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HISelectGraphics();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HISelectBindings();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HISelectUI();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HIUnselectSound();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HIUnselectGraphics();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HIUnselectBindings();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HIUnselectUI();

    UFUNCTION()
        void HIUpdateQuitVisiility();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void HISelectGoToMainMenu();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void HIUnselectGoToMainMenu();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void HISelectQuitGame();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void HIUnselectQuitGame();


protected:


private:
    UFUNCTION()
        void HISubMenuChanges();

    UFUNCTION()
        void HIQuitGame();

    UFUNCTION()
        void HIGoToMainMenu();

    UFUNCTION()
        void HIChangeResolution();

    UFUNCTION()
        void HIChangeWindowMode();

    UFUNCTION()
        void HIApplySettings();

    UFUNCTION()
        void HISoundButton();

    UFUNCTION()
        void HIGraphicsButton();

    UFUNCTION()
        void HIInputSettingsButton();

    UFUNCTION()
        void HIUIButton();

#pragma region UPDATE_GRAPHIC_INDEXES

    UFUNCTION()
        void HIChangeScreenResolutionRightIndex();

    UFUNCTION()
        void HIChangeScreenResolutionLeftIndex();

    UFUNCTION()
        void HIChangeWindowTypeFullIndex();

    UFUNCTION()
        void HIChangeWindowTypeWindowedIndex();

    UFUNCTION()
        void HIChangeBrightnessIndex();

    UFUNCTION()
        void HIChangeQualityIndex();

#pragma endregion

#pragma region UPDATE_SOUND_VALUES

    UFUNCTION()
        void HIChangeGeneralSoundValue(float _value);

    UFUNCTION()
        void HIChangeSFXValue(float _value);

    UFUNCTION()
        void HIChangeVoicesValue(float _value);

    UFUNCTION()
        void HIChangeAmbientSlider(float _value);

#pragma endregion

#pragma region BINDING_FUNCTIONS
    UFUNCTION()
        void HIChangeMouseSensivility(float _value);

    UFUNCTION()
        void HIReverseCameraIndexLeft();

    UFUNCTION()
        void HIReverseCameraIndexRight();

    UFUNCTION()
        void HIReverseCamera();

    UFUNCTION()
        void HIShowFPSIndexLeft();

    UFUNCTION()
        void HIShowFPSIndexRight();

    UFUNCTION()
        void HIShowFPS();

#pragma endregion

#pragma region UI_NAVIGATION
    UFUNCTION()
        void HISettingsButtonsNavigation(int _operator);

    UFUNCTION()
        void HIBindingsRowsNavigation(int _operator);

    UFUNCTION()
        void HIQuitNavigation(int _operator);

    UFUNCTION()
        void HIUpgradesNavigation(int _operator);

    UFUNCTION()
        void HIAchievementsNavigation(int _operator);

    UFUNCTION()
        void HISoundNavigation(int _operator);

    UFUNCTION()
        void HIGraphicsNavigation(int _operator);

    UFUNCTION()
        void HIBindingsNavigation(int _operator);

    UFUNCTION()
        void HIUiSettingsNavigation(int _operator);

    UFUNCTION()
        void HIOnChangeSoundValues(float _operator);

    UFUNCTION()
        void HIOnChangeGraphicValues(int _operator);

    UFUNCTION()
        void HIOnChangeUiValues(int _operator);

    UFUNCTION()
        void HIOnChangeBindingValues(int _operator, float _sensOperator);
#pragma endregion


};

// @AUTHOR: Guillermo Su�rez

#include "HIPauseMenu.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "UI/Utilities/HITextImageClass.h"
#include "UI/Utilities/HIButtonClass.h"
#include "UI/Utilities/HITextSwitcher.h"
#include "UI/Utilities/HIRowClassSwitcher.h"
#include "UI/Utilities/HISliderClass.h"
#include "UI/Utilities/HIRowClassSlider.h"
#include "Characters/VincentVolk/HIWerewolfController.h"
#include "Game/HIGameInstance.h"
#include <GameFramework/GameUserSettings.h>
#include "UI/Utilities/HITextImageClass.h"


bool UHIPauseMenu::Initialize()
{
    Super::Initialize();

    arrayIndex = 0;
    settingButtonsIndex = 0;
    quitButtonsIndex = 0;
    soundSettingsIndex = 0;
    bindingsIndex = 0;
    uiSettingsIndex = 0;
    graphicSettingsIndex = 0;
    bindingSettingsIndex = 0;
    reverseCameraIndex = 0;
    showFPSIndex = 0;
    screenResolutionIndex = screenResolutionRow->settingSwitcher->index;
    currentTranslation = 300.f;
    maxTranslation = currentTranslation + currentTranslation * 0.5f;
    minTranslation = -currentTranslation + currentTranslation * -0.5f;

    if (!controller)
    {
        controller = Cast<AHIWerewolfController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    }

    if (!gameInstance)
    {
        gameInstance = Cast<UHIGameInstance>(GetGameInstance());
    }

    if (!gameUserSettings)
    {
        gameUserSettings = UGameUserSettings::GetGameUserSettings(); // UGameUserSettings::GetGameUserSettings()

    }

    return true;
}

void UHIPauseMenu::NativePreConstruct()
{
    Super::NativePreConstruct();

    buttonsArray.Push(settingsImage);
    buttonsArray.Push(bindingsImage);
    buttonsArray.Push(exitImage);
    buttonsArray.Push(upgradesImage);
    buttonsArray.Push(achievementsImage);

    int index = 0;

    for (UHITextImageClass* iterator : buttonsArray)
    {
        iterator->textImageID = index;

        // Init image translations
        switch (index)
        {
        case 0:
            iterator->SetRenderTranslation(FVector2D(0, 0)); // settings
            break;
        case 1:
            iterator->SetRenderTranslation(FVector2D(currentTranslation, 0)); // bindings
            break;
        case 2:
            iterator->SetRenderTranslation(FVector2D(maxTranslation, 0)); // quit
            break;
        case 3:
            iterator->SetRenderTranslation(FVector2D(minTranslation, 0)); // upgrades
            break;
        case 4:
            iterator->SetRenderTranslation(FVector2D(-currentTranslation, 0)); // achievements
            break;
        default:
            break;
        }

        index++;
    }


    HIInitRows();
    HISubMenuChanges();
    HIGoToSettings();
}

void UHIPauseMenu::NativeConstruct()
{
    Super::NativeConstruct();

    bIsFocusable = true;

    //  SetFocus();

    leftButton->customButton->OnClicked.AddDynamic(this, &UHIPauseMenu::HILeftSubMenuMovement);
    rightButton->customButton->OnClicked.AddDynamic(this, &UHIPauseMenu::HIRightSubMenuMovement);

    screenResolutionRow->settingSwitcher->leftSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIChangeScreenResolutionLeftIndex);
    screenResolutionRow->settingSwitcher->rightSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIChangeScreenResolutionRightIndex);

    windowTypeRow->settingSwitcher->leftSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIChangeWindowTypeFullIndex);
    windowTypeRow->settingSwitcher->rightSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIChangeWindowTypeWindowedIndex);

    brightnessRow->settingSwitcher->leftSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIChangeBrightnessIndex);
    brightnessRow->settingSwitcher->rightSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIChangeBrightnessIndex);

    qualityRow->settingSwitcher->leftSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIChangeQualityIndex);
    qualityRow->settingSwitcher->rightSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIChangeQualityIndex);

    generalSoundSlider->customSlider->mainSlider->OnValueChanged.AddDynamic(this, &UHIPauseMenu::HIChangeGeneralSoundValue);
    sfxSlider->customSlider->mainSlider->OnValueChanged.AddDynamic(this, &UHIPauseMenu::HIChangeSFXValue);
    voicesSlider->customSlider->mainSlider->OnValueChanged.AddDynamic(this, &UHIPauseMenu::HIChangeVoicesValue);
    ambientSlider->customSlider->mainSlider->OnValueChanged.AddDynamic(this, &UHIPauseMenu::HIChangeAmbientSlider);

    mouseSensivilitySlider->customSlider->mainSlider->OnValueChanged.AddDynamic(this, &UHIPauseMenu::HIChangeMouseSensivility);

    reverseCameraSwitcher->settingSwitcher->leftSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIReverseCameraIndexLeft);
    reverseCameraSwitcher->settingSwitcher->rightSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIReverseCameraIndexRight);

    showFPSSwitcher->settingSwitcher->leftSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIShowFPSIndexLeft);
    showFPSSwitcher->settingSwitcher->rightSwitcher->OnClicked.AddDynamic(this, &UHIPauseMenu::HIShowFPSIndexRight);

    soundButton->customButton->OnClicked.AddDynamic(this, &UHIPauseMenu::HISoundButton);
    graphicsButton->customButton->OnClicked.AddDynamic(this, &UHIPauseMenu::HIGraphicsButton);
    inputSettingsButton->customButton->OnClicked.AddDynamic(this, &UHIPauseMenu::HIInputSettingsButton);
    uiButton->customButton->OnClicked.AddDynamic(this, &UHIPauseMenu::HIUIButton);

    quitButton->customButton->OnClicked.AddDynamic(this, &UHIPauseMenu::HIQuitGame);
    mainMenuButton->customButton->OnClicked.AddDynamic(this, &UHIPauseMenu::HIGoToMainMenu);
    applyButton->customButton->OnClicked.AddDynamic(this, &UHIPauseMenu::HIApplySettings);

    HISettingsButtonsNavigation(0);
    HIQuitNavigation(0);
    HISelectSound();
    HISelectGoToMainMenu();
    HIUpdateVisibilities();
}

void UHIPauseMenu::HIRightSubMenuMovement()
{
    float xValue = 0.f;
    arrayIndex++;

    if (arrayIndex > buttonsArray.Num() - 1)
    {
        arrayIndex = 0;
    }

    for (UHITextImageClass* iterator : buttonsArray)
    {
        // Cuando la imagen est� a la izquierda del todo, 
        // en la siguiente iteraci�n pasa a la derecha del todo -600 --> 600
        if (iterator->RenderTransform.Translation.X <= minTranslation)
        {
            iterator->SetRenderTranslation(FVector2D(maxTranslation, 0.f));
        }
        else if (iterator->RenderTransform.Translation.X == maxTranslation)
        {
            iterator->SetRenderTranslation(FVector2D(currentTranslation, 0.f));
        }
        else if (iterator->RenderTransform.Translation.X == -currentTranslation)
        {
            iterator->SetRenderTranslation(FVector2D(minTranslation, 0.f));
        }
        else // equivale a la posici�n 0 y 300
        {
            xValue = iterator->RenderTransform.Translation.X -= currentTranslation;
            iterator->SetRenderTranslation(FVector2D(xValue, 0.f));
        }

        HISubMenuChanges();
        HIUpdateVisibilities();
    }

    widgSwitcher->SetActiveWidgetIndex(arrayIndex);

    /*if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(arrayIndex));
    }*/
}

void UHIPauseMenu::HILeftSubMenuMovement()
{
    float xValue = 0.f;
    arrayIndex--;

    if (arrayIndex < 0)
    {
        arrayIndex = buttonsArray.Num() - 1;
    }

    for (UHITextImageClass* iterator : buttonsArray)
    {
        // derecha del todo pasa a la izquierda del todo
        if (iterator->RenderTransform.Translation.X >= maxTranslation)
        {
            iterator->SetRenderTranslation(FVector2D(minTranslation, 0.f));
        }
        else if (iterator->RenderTransform.Translation.X == minTranslation)
        {
            iterator->SetRenderTranslation(FVector2D(-currentTranslation, 0.f));
        }
        else if (iterator->RenderTransform.Translation.X == currentTranslation)
        {
            iterator->SetRenderTranslation(FVector2D(maxTranslation, 0.f));
        }
        else // posicion 0 y -300
        {
            xValue = iterator->RenderTransform.Translation.X += currentTranslation;
            iterator->SetRenderTranslation(FVector2D(xValue, 0.f));
        }

        HISubMenuChanges();
        HIUpdateVisibilities();
    }

    widgSwitcher->SetActiveWidgetIndex(arrayIndex);

    /*if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(arrayIndex));
    }*/
}

bool UHIPauseMenu::HIGoToSettings()
{
    for (UHITextImageClass* iterator : buttonsArray)
    {
        if (iterator->textImageID == 0 && iterator->RenderTransform.Translation.X == 0)
        {
            return true;
        }
    }

    return false;
}

void UHIPauseMenu::HISubMenuChanges()
{
    for (UHITextImageClass* iterator : buttonsArray)
    {
        if (iterator->RenderTransform.Translation.X == 0)
        {
            iterator->SetRenderOpacity(1.f);
            iterator->SetRenderScale(FVector2D(1.f, 1.f));
        }
        else if (iterator->RenderTransform.Translation.X == -currentTranslation || iterator->RenderTransform.Translation.X == currentTranslation)
        {
            iterator->SetRenderOpacity(0.5f);
            iterator->SetRenderScale(FVector2D(0.6f, 0.6f));
        }
        else if (iterator->RenderTransform.Translation.X == -minTranslation || iterator->RenderTransform.Translation.X == minTranslation)
        {
            iterator->SetRenderOpacity(0.2f);
            iterator->SetRenderScale(FVector2D(0.3f, 0.3f));
        }
    }
}

void UHIPauseMenu::HIQuitGame()
{
    if (controller)
    {
        controller->ConsoleCommand("quit");
    }
}

void UHIPauseMenu::HIGoToMainMenu()
{
    UGameplayStatics::OpenLevel(this, FName(TEXT("MainMenu")), true);
}

void UHIPauseMenu::HIChangeResolution()
{
    if (gameUserSettings)
    {
        if (screenResolutionRow->settingSwitcher->index == 0)
        {
            gameUserSettings->SetScreenResolution(FIntPoint(1280, 720));
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::FromInt(screenResolutionRow->settingSwitcher->index));
            }
        }
        else if (screenResolutionRow->settingSwitcher->index == 1)
        {
            gameUserSettings->SetScreenResolution((FIntPoint(1920, 1080)));
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::FromInt(screenResolutionRow->settingSwitcher->index));
            }
        }
        else if (screenResolutionRow->settingSwitcher->index == 2)
        {
            gameUserSettings->SetScreenResolution((FIntPoint(2560, 1440)));
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::FromInt(screenResolutionRow->settingSwitcher->index));
            }
        }
    }
}

void UHIPauseMenu::HIChangeWindowMode()
{
    if (gameUserSettings)
    {
        if (windowTypeRow->settingSwitcher->index == 0)
        {
            gameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
        }
        else
        {
            gameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
        }
    }
}

void UHIPauseMenu::HIApplySettings()
{
    if (gameUserSettings)
    {
        gameUserSettings->ApplySettings(true);
    }
}

void UHIPauseMenu::HISoundButton()
{

    settingButtonsIndex = 0;

    graphicsButton->HIClearFocus();
    uiButton->HIClearFocus();
    inputSettingsButton->HIClearFocus();
    soundButton->HIFocused();

    settingsSwitcher->SetActiveWidgetIndex(settingButtonsIndex);
}

void UHIPauseMenu::HIGraphicsButton()
{
    settingButtonsIndex = 1;

    soundButton->HIClearFocus();
    inputSettingsButton->HIClearFocus();
    uiButton->HIClearFocus();
    graphicsButton->HIFocused();

    settingsSwitcher->SetActiveWidgetIndex(settingButtonsIndex);
}

void UHIPauseMenu::HIInputSettingsButton()
{
    settingButtonsIndex = 2;

    graphicsButton->HIClearFocus();
    uiButton->HIClearFocus();
    soundButton->HIClearFocus();
    inputSettingsButton->HIFocused();


    settingsSwitcher->SetActiveWidgetIndex(settingButtonsIndex);
}

void UHIPauseMenu::HIUIButton()
{
    settingButtonsIndex = 3;

    soundButton->HIClearFocus();
    inputSettingsButton->HIClearFocus();
    graphicsButton->HIClearFocus();
    uiButton->HIFocused();

    settingsSwitcher->SetActiveWidgetIndex(settingButtonsIndex);
}

void UHIPauseMenu::HIInitRows()
{
    if (gameInstance)
    {
        if (screenResolutionRow)
        {
            screenResolutionRow->settingSwitcher->HIUpdateIndex(gameInstance->screenResolutionIndex);
            screenResolutionRow->HIFocused();
        }

        if (windowTypeRow)
        {
            windowTypeRow->settingSwitcher->HIUpdateIndex(gameInstance->windowTypeIndex);
        }

        if (brightnessRow)
        {
            brightnessRow->settingSwitcher->HIUpdateIndex(gameInstance->brightnessIndex);
        }

        if (qualityRow)
        {
            qualityRow->settingSwitcher->HIUpdateIndex(gameInstance->qualityIndex);
        }

        if (generalSoundSlider)
        {
            generalSoundSlider->HISetValue(gameInstance->generalSoundValue);
            generalSoundSlider->HIFocused();
        }

        if (sfxSlider)
        {
            sfxSlider->HISetValue(gameInstance->sfxValue);
        }

        if (voicesSlider)
        {
            voicesSlider->HISetValue(gameInstance->voicesValue);
        }

        if (ambientSlider)
        {
            ambientSlider->HISetValue(gameInstance->ambientValue);
        }

        if (subtitlesSwitcher)
        {
            subtitlesSwitcher->settingSwitcher->HIUpdateIndex(gameInstance->subtitlesIndex);
            subtitlesSwitcher->HIFocused();
        }

        if (colorbindSwitcher)
        {
            colorbindSwitcher->settingSwitcher->HIUpdateIndex(gameInstance->colorbindIndex);
        }

        if (mouseSensivilitySlider)
        {
            mouseSensivilitySlider->customSlider->HISetMinValue(8.f);
            mouseSensivilitySlider->customSlider->HISetMaxValue(50.f);
            mouseSensivilitySlider->HISetValue(gameInstance->mouseSensivility);
            mouseSensivilitySlider->HIFocused();
        }

        if (reverseCameraSwitcher)
        {
            reverseCameraSwitcher->settingSwitcher->HIUpdateIndex(gameInstance->reverseCameraIndex);
        }

        if (showFPSSwitcher)
        {
            showFPSSwitcher->settingSwitcher->HIUpdateIndex(gameInstance->showFPSIndex);
        }
    }
}

void UHIPauseMenu::HIInitVincentHUD()
{
    if (!vincentHUD)
    {
        vincentHUD = UHIGameData::HIGetPlayerWerewolf()->widgetref;
    }
}

#pragma region UPDATE_GRAPHIC_INDEXES

void UHIPauseMenu::HIChangeScreenResolutionRightIndex()
{
    ++screenResolutionIndex;

    if (screenResolutionIndex > 2)
    {
        screenResolutionIndex = 0;
    }

    gameInstance->screenResolutionIndex = screenResolutionIndex;
    screenResolutionRow->settingSwitcher->HIUpdateIndex(gameInstance->screenResolutionIndex);

    HIChangeResolution();
}

void UHIPauseMenu::HIChangeScreenResolutionLeftIndex()
{
    --screenResolutionIndex;

    if (screenResolutionIndex < 0)
    {
        screenResolutionIndex = 2;
    }

    gameInstance->screenResolutionIndex = screenResolutionIndex;
    screenResolutionRow->settingSwitcher->HIUpdateIndex(gameInstance->screenResolutionIndex);

    HIChangeResolution();
}

void UHIPauseMenu::HIChangeWindowTypeFullIndex()
{
    ++screenModeIndex;

    if (screenModeIndex > 1)
    {
        screenModeIndex = 0;
    }

    gameInstance->windowTypeIndex = screenModeIndex;
    windowTypeRow->settingSwitcher->HIUpdateIndex(screenModeIndex);

    HIChangeWindowMode();
}

void UHIPauseMenu::HIChangeWindowTypeWindowedIndex()
{
    --screenModeIndex;

    if (screenModeIndex < 0)
    {
        screenModeIndex = 1;
    }

    gameInstance->windowTypeIndex = screenModeIndex;
    windowTypeRow->settingSwitcher->HIUpdateIndex(screenModeIndex);

    HIChangeWindowMode();
}

void UHIPauseMenu::HIChangeBrightnessIndex()
{
    gameInstance->brightnessIndex = brightnessRow->settingSwitcher->index;
}

void UHIPauseMenu::HIChangeQualityIndex()
{
    gameInstance->qualityIndex = qualityRow->settingSwitcher->index;
}

#pragma endregion
#pragma region UPDATE_SOUND_VALUES

void UHIPauseMenu::HIChangeGeneralSoundValue(float _value)
{
    gameInstance->generalSoundValue = _value;
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), generalSoundMix, generalSoundClass, gameInstance->generalSoundValue);
}

void UHIPauseMenu::HIChangeSFXValue(float _value)
{
    gameInstance->sfxValue = _value;
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), sfxSoundMix, sfxSoundClass, gameInstance->sfxValue);
}

void UHIPauseMenu::HIChangeVoicesValue(float _value)
{
    gameInstance->voicesValue = _value;
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), voicesSoundMix, voicesSoundClass, gameInstance->voicesValue);
}

void UHIPauseMenu::HIChangeAmbientSlider(float _value)
{
    gameInstance->ambientValue = _value;
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), ambientSoundMix, ambientSoundClass, gameInstance->ambientValue);
}

void UHIPauseMenu::HIChangeMouseSensivility(float _value)
{
    gameInstance->mouseSensivility = _value;
}

void UHIPauseMenu::HIReverseCameraIndexLeft()
{
    --reverseCameraIndex;

    if (reverseCameraIndex < 0)
    {
        reverseCameraIndex = 3;
    }

    reverseCameraSwitcher->settingSwitcher->HIUpdateIndex(reverseCameraIndex);
    HIReverseCamera();
}

void UHIPauseMenu::HIReverseCameraIndexRight()
{
    ++reverseCameraIndex;

    if (reverseCameraIndex > 3)
    {
        reverseCameraIndex = 0;
    }

    reverseCameraSwitcher->settingSwitcher->HIUpdateIndex(reverseCameraIndex);
    HIReverseCamera();
}

void UHIPauseMenu::HIReverseCamera()
{
    if (reverseCameraIndex == 0)
    {
        gameInstance->reverseYCamera = 1;
        gameInstance->reverseXCamera = 1;
    }
    else if (reverseCameraIndex == 3)
    {
        gameInstance->reverseYCamera = -1;
        gameInstance->reverseXCamera = -1;
    }
    else if (reverseCameraIndex == 2)
    {
        gameInstance->reverseYCamera = -1;
        gameInstance->reverseXCamera = 1;
    }
    else if (reverseCameraIndex == 1)
    {
        gameInstance->reverseYCamera = 1;
        gameInstance->reverseXCamera = -1;
    }
}

void UHIPauseMenu::HIShowFPSIndexLeft()
{
    --showFPSIndex;

    if (showFPSIndex < 0)
    {
        showFPSIndex = 1;
    }

    showFPSSwitcher->settingSwitcher->HIUpdateIndex(showFPSIndex);
    HIShowFPS();
}

void UHIPauseMenu::HIShowFPSIndexRight()
{
    ++showFPSIndex;

    if (showFPSIndex > 1)
    {
        showFPSIndex = 0;
    }

    showFPSSwitcher->settingSwitcher->HIUpdateIndex(showFPSIndex);
    HIShowFPS();
}

void UHIPauseMenu::HIShowFPS()
{
    gameInstance->showFPSIndex = showFPSIndex;

    if (showFPSIndex == 0)
    {
        vincentHUD->HISetFPSVisibilityText(false);

    }
    else if (showFPSIndex == 1)
    {
        vincentHUD->HISetFPSVisibilityText(true);

    }
}

void UHIPauseMenu::HISettingsButtonsNavigation(int _operator)
{
    if (arrayIndex == 0)
    {
        settingButtonsIndex += _operator;

        if (settingButtonsIndex > 3)
        {
            settingButtonsIndex = 0;
        }
        else if (settingButtonsIndex < 0)
        {
            settingButtonsIndex = 3;
        }

        switch (settingButtonsIndex)
        {
        case 0:
            HISoundButton();
            break;
        case 1:
            HIGraphicsButton();
            break;
        case 2:
            HIInputSettingsButton();
            break;
        case 3:
            HIUIButton();
            break;
        default:

            break;
        }
    }
}

void UHIPauseMenu::HIBindingsRowsNavigation(int _operator)
{
    if (arrayIndex == 1)
    {
        bindingsIndex += _operator;

        if (bindingsIndex > 2)
        {
            bindingsIndex = 2;
        }
        else if (bindingsIndex < 0)
        {
            bindingsIndex = 0;
        }

        switch (bindingsIndex)
        {
        case 0:
            mouseSensivilitySlider->HIFocused();
            reverseCameraSwitcher->HIClearFocus();
            showFPSSwitcher->HIClearFocus();
            break;
        case 1:
            mouseSensivilitySlider->HIClearFocus();
            reverseCameraSwitcher->HIFocused();
            showFPSSwitcher->HIClearFocus();
            break;
        case 2:
            mouseSensivilitySlider->HIClearFocus();
            reverseCameraSwitcher->HIClearFocus();
            showFPSSwitcher->HIFocused();
            break;
        default:

            break;
        }
    }
}

void UHIPauseMenu::HIQuitNavigation(int _operator)
{
    if (arrayIndex == 2)
    {
        quitButtonsIndex += _operator;

        if (quitButtonsIndex > 1)
        {
            quitButtonsIndex = 0;
        }
        else if (quitButtonsIndex < 0)
        {
            quitButtonsIndex = 1;
        }

        if (quitButtonsIndex == 0)
        {
            mainMenuButton->HIClearFocus();
            quitButton->HIFocused();
        }
        else if (quitButtonsIndex == 1)
        {
            quitButton->HIClearFocus();
            mainMenuButton->HIFocused();
        }
    }
    else
    {
        quitButtonsIndex = 0;
        mainMenuButton->HIClearFocus();
        quitButton->HIFocused();
    }

    HIUpdateQuitVisiility();
}

void UHIPauseMenu::HIUpgradesNavigation(int _operator)
{

}

void UHIPauseMenu::HIAchievementsNavigation(int _operator)
{

}

void UHIPauseMenu::HISoundNavigation(int _operator)
{
    if (arrayIndex == 0 && settingButtonsIndex == 0)
    {
        soundSettingsIndex += _operator;

        if (soundSettingsIndex > 3)
        {
            soundSettingsIndex = 3;
        }
        else if (soundSettingsIndex < 0)
        {
            soundSettingsIndex = 0;
        }

        switch (soundSettingsIndex)
        {
        case 0:
            sfxSlider->HIClearFocus();
            generalSoundSlider->HIFocused();
            break;
        case 1:
            generalSoundSlider->HIClearFocus();
            voicesSlider->HIClearFocus();
            sfxSlider->HIFocused();
            break;
        case 2:
            sfxSlider->HIClearFocus();
            ambientSlider->HIClearFocus();
            voicesSlider->HIFocused();
            break;
        case 3:
            voicesSlider->HIClearFocus();
            ambientSlider->HIFocused();
            break;
        default:

            break;
        }
    }
}

void UHIPauseMenu::HIGraphicsNavigation(int _operator)
{
    if (arrayIndex == 0 && settingButtonsIndex == 1)
    {
        graphicSettingsIndex += _operator;

        if (graphicSettingsIndex > 3)
        {
            graphicSettingsIndex = 3;
        }
        else if (graphicSettingsIndex < 0)
        {
            graphicSettingsIndex = 0;
        }

        switch (graphicSettingsIndex)
        {
        case 0:
            windowTypeRow->HIClearFocus();
            screenResolutionRow->HIFocused();
            break;
        case 1:
            screenResolutionRow->HIClearFocus();
            brightnessRow->HIClearFocus();
            windowTypeRow->HIFocused();
            break;
        case 2:
            windowTypeRow->HIClearFocus();
            qualityRow->HIClearFocus();
            brightnessRow->HIFocused();
            break;
        case 3:
            brightnessRow->HIClearFocus();
            qualityRow->HIFocused();
            break;
        default:

            break;
        }

    }
}

void UHIPauseMenu::HIBindingsNavigation(int _operator)
{
    if (arrayIndex == 0 && settingButtonsIndex == 2)
    {
        bindingSettingsIndex += _operator;

        if (bindingSettingsIndex > 2)
        {
            bindingSettingsIndex = 2;
        }
        else if (bindingSettingsIndex < 0)
        {
            bindingSettingsIndex = 0;
        }

        switch (bindingSettingsIndex)
        {
        case 0:
            reverseCameraSwitcher->HIClearFocus();
            showFPSSwitcher->HIClearFocus();
            mouseSensivilitySlider->HIFocused();
            break;
        case 1:
            showFPSSwitcher->HIClearFocus();
            mouseSensivilitySlider->HIClearFocus();
            reverseCameraSwitcher->HIFocused();
            break;
        case 2:
            mouseSensivilitySlider->HIClearFocus();
            reverseCameraSwitcher->HIClearFocus();
            showFPSSwitcher->HIFocused();
            break;
        default:

            break;
        }
    }
}

void UHIPauseMenu::HIUiSettingsNavigation(int _operator)
{
    if (arrayIndex == 0 && settingButtonsIndex == 3)
    {
        uiSettingsIndex += _operator;

        if (uiSettingsIndex > 1)
        {
            uiSettingsIndex = 1;
        }
        else if (uiSettingsIndex < 0)
        {
            uiSettingsIndex = 0;
        }

        switch (uiSettingsIndex)
        {
        case 0:
            colorbindSwitcher->HIClearFocus();
            subtitlesSwitcher->HIFocused();
            break;
        case 1:
            subtitlesSwitcher->HIClearFocus();
            colorbindSwitcher->HIFocused();
            break;
        default:

            break;
        }
    }
}

void UHIPauseMenu::HIOnChangeSoundValues(float _operator)
{
    if (arrayIndex == 0 && settingButtonsIndex == 0)
    {
        float gAux = generalSoundSlider->HIGetValue();
        float sfxAux = sfxSlider->HIGetValue();
        float vAux = voicesSlider->HIGetValue();
        float amAux = ambientSlider->HIGetValue();

        switch (soundSettingsIndex)
        {
        case 0:
            gameInstance->generalSoundValue = gAux + _operator;
            generalSoundSlider->HISetValue(gameInstance->generalSoundValue);
            HIChangeGeneralSoundValue(gameInstance->generalSoundValue);
            break;
        case 1:
            gameInstance->sfxValue = sfxAux + _operator;
            sfxSlider->HISetValue(gameInstance->sfxValue);
            HIChangeSFXValue(gameInstance->sfxValue);
            break;
        case 2:
            gameInstance->voicesValue = vAux + _operator;
            voicesSlider->HISetValue(gameInstance->voicesValue);
            HIChangeVoicesValue(gameInstance->voicesValue);
            break;
        case 3:
            gameInstance->ambientValue = amAux + _operator;
            ambientSlider->HISetValue(gameInstance->ambientValue);
            HIChangeAmbientSlider(gameInstance->ambientValue);
        default:

            break;
        }
    }
}

void UHIPauseMenu::HIOnChangeGraphicValues(int _operator)
{
    if (arrayIndex == 0 && settingButtonsIndex == 1)
    {
        int scAux = screenResolutionRow->settingSwitcher->index;
        int wtAux = windowTypeRow->settingSwitcher->index;
        int bAux = brightnessRow->settingSwitcher->index;
        int qAux = qualityRow->settingSwitcher->index;

        switch (graphicSettingsIndex)
        {
        case 0:
            gameInstance->screenResolutionIndex = scAux + _operator;
            screenResolutionRow->settingSwitcher->HIUpdateIndex(gameInstance->screenResolutionIndex);
            HIChangeResolution();

            break;
        case 1:
            gameInstance->windowTypeIndex = wtAux + _operator;
            windowTypeRow->settingSwitcher->HIUpdateIndex(gameInstance->windowTypeIndex);
            HIChangeWindowMode();
            break;
        case 2:
            gameInstance->brightnessIndex = bAux + _operator;
            brightnessRow->settingSwitcher->HIUpdateIndex(gameInstance->brightnessIndex);
            // @TODO: Implementar brightness
            break;
        case 3:
            gameInstance->qualityIndex = qAux + _operator;
            qualityRow->settingSwitcher->HIUpdateIndex(gameInstance->qualityIndex);
            // @TODO: Implementar quality
            break;
        default:

            break;
        }
    }
}

void UHIPauseMenu::HIOnChangeBindingValues(int _operator, float _sensOperator)
{
    if (arrayIndex == 0 && settingButtonsIndex == 2)
    {
        float sensAux = mouseSensivilitySlider->HIGetValue();
        int revAux = reverseCameraSwitcher->settingSwitcher->index;
        int showFPSAux = showFPSSwitcher->settingSwitcher->index;

        switch (bindingSettingsIndex)
        {
        case 0:
            gameInstance->mouseSensivility = sensAux + _sensOperator;
            mouseSensivilitySlider->HISetValue(gameInstance->mouseSensivility);
            HIChangeMouseSensivility(gameInstance->mouseSensivility);
            break;
        case 1:
            reverseCameraIndex = revAux + _operator;

            if (reverseCameraIndex > 3)
            {
                reverseCameraIndex = 0;
            }
            else if (reverseCameraIndex < 0)
            {
                reverseCameraIndex = 3;
            }

            gameInstance->reverseCameraIndex = reverseCameraIndex;
            reverseCameraSwitcher->settingSwitcher->HIUpdateIndex(reverseCameraIndex);
            HIReverseCamera();
            break;
        case 2:
            showFPSIndex = showFPSAux + _operator;

            if (showFPSIndex > 1)
            {
                showFPSIndex = 0;
            }
            else if (showFPSIndex < 0)
            {
                showFPSIndex = 1;
            }

            gameInstance->showFPSIndex = showFPSIndex;
            showFPSSwitcher->settingSwitcher->HIUpdateIndex(showFPSIndex);
            HIShowFPS();
            break;
        default:
            break;
        }
    }
}

void UHIPauseMenu::HIOnChangeUiValues(int _operator)
{
    if (arrayIndex == 0 && settingButtonsIndex == 3)
    {
        int subAux = subtitlesSwitcher->settingSwitcher->index;
        int cbAux = colorbindSwitcher->settingSwitcher->index;

        switch (uiSettingsIndex)
        {
        case 0:
            gameInstance->subtitlesIndex = subAux + _operator;
            subtitlesSwitcher->settingSwitcher->HIUpdateIndex(gameInstance->subtitlesIndex);
            break;
        case 1:
            gameInstance->colorbindIndex = cbAux + _operator;
            colorbindSwitcher->settingSwitcher->HIUpdateIndex(gameInstance->colorbindIndex);
            break;
        default:

            break;
        }
    }
}

void UHIPauseMenu::HISelectedSettings_Implementation()
{
    if (arrayIndex == 0)
    {
        settingsImage->customImage->SetVisibility(ESlateVisibility::HitTestInvisible);
    }
    else
    {
        settingsImage->customImage->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UHIPauseMenu::HISelectedBindings_Implementation()
{
    if (arrayIndex == 1)
    {
        bindingsImage->customImage->SetVisibility(ESlateVisibility::HitTestInvisible);
    }
    else
    {
        bindingsImage->customImage->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UHIPauseMenu::HISelectedQuit_Implementation()
{
    if (arrayIndex == 2)
    {
        exitImage->customImage->SetVisibility(ESlateVisibility::HitTestInvisible);
    }
    else
    {
        exitImage->customImage->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UHIPauseMenu::HISelectedUpgrades_Implementation()
{
    if (arrayIndex == 3)
    {
        upgradesImage->customImage->SetVisibility(ESlateVisibility::HitTestInvisible);
    }
    else
    {
        upgradesImage->customImage->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UHIPauseMenu::HISelectedAchievments_Implementation()
{
    if (arrayIndex == 4)
    {
        achievementsImage->customImage->SetVisibility(ESlateVisibility::HitTestInvisible);
    }
    else
    {
        achievementsImage->customImage->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UHIPauseMenu::HIUpdateVisibilities()
{
    HISelectedSettings();
    HISelectedBindings();
    HISelectedQuit();
    HISelectedUpgrades();
    HISelectedAchievments();
}

void UHIPauseMenu::HIUpdateSubmenuVisibility()
{
    if (arrayIndex == 0)
    {
        switch (settingButtonsIndex)
        {
        case 0:
            HISelectSound();
            HIUnselectGraphics();
            HIUnselectBindings();
            HIUnselectUI();
            break;
        case 1:
            HISelectGraphics();
            HIUnselectSound();
            HIUnselectBindings();
            HIUnselectUI();
            break;
        case 2:
            HISelectBindings();
            HIUnselectSound();
            HIUnselectGraphics();
            HIUnselectUI();
            break;
        case 3:
            HISelectUI();
            HIUnselectSound();
            HIUnselectGraphics();
            HIUnselectBindings();
            break;
        default:
            break;
        }
    }
}

void UHIPauseMenu::HISelectSound_Implementation()
{

}

void UHIPauseMenu::HISelectGraphics_Implementation()
{

}

void UHIPauseMenu::HISelectBindings_Implementation()
{

}

void UHIPauseMenu::HISelectUI_Implementation()
{

}

void UHIPauseMenu::HIUnselectSound_Implementation()
{

}

void UHIPauseMenu::HIUnselectGraphics_Implementation()
{

}

void UHIPauseMenu::HIUnselectBindings_Implementation()
{

}

void UHIPauseMenu::HIUnselectUI_Implementation()
{

}

void UHIPauseMenu::HIUpdateQuitVisiility()
{
    if (arrayIndex == 2)
    {
        if (quitButtonsIndex == 0)
        {
            HISelectGoToMainMenu();
            HIUnselectQuitGame();
        }
        else
        {
            HISelectQuitGame();
            HIUnselectGoToMainMenu();
        }
    }
}

#pragma endregion

FReply UHIPauseMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    Super::NativeOnKeyDown(InGeometry, InKeyEvent);

    FKey customKey = InKeyEvent.GetKey();

    /*
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::FromInt(arrayIndex));
        }*/

    if (customKey.GetDisplayName().ToString() == TEXT("Gamepad Right Shoulder"))
    {
        HIRightSubMenuMovement();

        return FReply::Handled();
    }
    else if (customKey.GetDisplayName().ToString() == TEXT("Gamepad Left Shoulder"))
    {
        HILeftSubMenuMovement();

        return FReply::Handled();
    }
    else if (customKey.GetDisplayName().ToString() == TEXT("Gamepad Right Trigger"))
    {
        HISettingsButtonsNavigation(1);
        HIUpdateSubmenuVisibility();

        return FReply::Handled();
    }
    else if (customKey.GetDisplayName().ToString() == TEXT("Gamepad Left Trigger"))
    {
        HISettingsButtonsNavigation(-1);
        HIUpdateSubmenuVisibility();

        return FReply::Handled();
    }
    else if (customKey.GetDisplayName().ToString() == TEXT("Gamepad D-pad Right"))
    {
        HIOnChangeSoundValues(0.05f);
        HIOnChangeGraphicValues(1);
        HIOnChangeUiValues(1);
        HIQuitNavigation(1);
        HIOnChangeBindingValues(1, 2.f);


        return FReply::Handled();
    }
    else if (customKey.GetDisplayName().ToString() == TEXT("Gamepad D-pad Left"))
    {
        HIOnChangeSoundValues(-0.05f);
        HIOnChangeGraphicValues(-1);
        HIOnChangeUiValues(-1);
        HIQuitNavigation(-1);
        HIOnChangeBindingValues(-1, -2.f);

        return FReply::Handled();
    }
    else if (customKey.GetDisplayName().ToString() == TEXT("Gamepad D-pad Down") || customKey.GetDisplayName().ToString() == TEXT("Down"))
    {
        HISoundNavigation(1);
        HIGraphicsNavigation(1);
        HIUiSettingsNavigation(1);
        HIBindingsRowsNavigation(1);
        HIBindingsNavigation(1);
    }
    else if (customKey.GetDisplayName().ToString() == TEXT("Gamepad D-pad Up") || customKey.GetDisplayName().ToString() == TEXT("Up"))
    {
        HISoundNavigation(-1);
        HIGraphicsNavigation(-1);
        HIUiSettingsNavigation(-1);
        HIBindingsRowsNavigation(-1);
        HIBindingsNavigation(-1);
    }
    else if (customKey.GetDisplayName().ToString() == TEXT("Gamepad Face Button Bottom"))
    {
        switch (arrayIndex)
        {
        case 0:

            break;
        case 1:
            break;
        case 2:
            if (quitButtonsIndex == 0)
            {
                HIGoToMainMenu();
            }
            else if (quitButtonsIndex == 1)
            {
                HIQuitGame();
            }
            break;
        case 3:

            break;
        case 4:

            break;
        default:

            break;
        }
    }
    else if (customKey.GetDisplayName().ToString() == TEXT("Escape") || customKey.GetDisplayName().ToString() == TEXT("Gamepad Special Right"))
    {
        SetVisibility(ESlateVisibility::Collapsed);
        controller->SetInputMode(FInputModeGameOnly());
        UGameplayStatics::SetGamePaused(GetWorld(), false);
        controller->GetPawn<AHIWerewolf>()->widgetref->SetVisibility(ESlateVisibility::Visible);
        controller->bShowMouseCursor = false;

        return FReply::Handled();
    }

    return FReply::Unhandled();
}

int UHIPauseMenu::HIGetFPSIndex()
{
    return showFPSIndex;
}

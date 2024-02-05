// @AUTHORS: Guillermo Su�rez


#include "HIMainMenu.h"
#include "Components/Button.h"
#include "Components/PanelWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Game/HIGameData.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Utilities/HIButtonClass.h"

bool UHIMainMenu::Initialize()
{
    Super::Initialize();

    buttonsIndex = 0;

    return true;
}

void UHIMainMenu::NativePreConstruct()
{
    Super::NativePreConstruct();
}

void UHIMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    //  playButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HIPlayButton);
    continueButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HIContinueButton);
    levelSelectorButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HILevelSelectorButton);
    playgroundButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HIPlaygroundButton);
    settingsButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HISettingsButton);
    creditsButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HICreditsButton);
    exitButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HIQuitGame);

    backLevelButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HIBackLevelButton);
    backSettingsButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HIBackSettingsButton);

    graphicsButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HIGraphicsButton);
    soundButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HISoundButton);
    inputSettingsButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HIInputSettingsButton);
    uiButton->customButton->OnClicked.AddDynamic(this, &UHIMainMenu::HIUIButton);
}

void UHIMainMenu::HIPlayButton()
{
    HIOpenLevel();
    UGameplayStatics::OpenLevel(this, FName(TEXT("Lvl_Steelheart")), true);
    UHIGameData::HIClearStaticReferences();
}


int UHIMainMenu::HIGetButtonIndex()
{
    return buttonsIndex;
}


void UHIMainMenu::HIContinueButton() // @TODO: Hay que hacer carga y guardado de datos
{
    //                        ****** PROVISIONAL *******
    //HIOpenLevel();
    //UGameplayStatics::OpenLevel(this, FName(TEXT("Lvl_Steelheart")), false);
    //UHIGameData::HIClearStaticReferences();
}

void UHIMainMenu::HIPlaygroundButton() // @TODO: Hay que hacer carga y guardado de datos
{
    //                        ****** PROVISIONAL *******
    //HIOpenLevel();
    //UGameplayStatics::OpenLevel(this, FName(TEXT("Lvl_Steelheart")), false);
    //UHIGameData::HIClearStaticReferences();
}

void UHIMainMenu::HIBackLevelButton()
{
    // mainButtonsPanel->SetVisibility(ESlateVisibility::Visible);
    // levelSelectorPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UHIMainMenu::HIBackSettingsButton()
{
    // mainButtonsPanel->SetVisibility(ESlateVisibility::Visible);
    // settingsCanvas->SetVisibility(ESlateVisibility::Collapsed);
}

void UHIMainMenu::HILevelSelectorButton()
{
    // mainButtonsPanel->SetVisibility(ESlateVisibility::Collapsed);
    // levelSelectorPanel->SetVisibility(ESlateVisibility::Visible);
}

void UHIMainMenu::HISettingsButton()
{
    // mainButtonsPanel->SetVisibility(ESlateVisibility::Collapsed);
    // settingsCanvas->SetVisibility(ESlateVisibility::Visible);
}

void UHIMainMenu::HICreditsButton()
{
	// mainButtonsPanel->SetVisibility(ESlateVisibility::Collapsed);
	// settingsCanvas->SetVisibility(ESlateVisibility::Visible);
}

void UHIMainMenu::HIQuitGame()
{
    HIQuitGameEvent();
}

void UHIMainMenu::HISoundButton()
{
    //settingsSwitcher->SetActiveWidgetIndex(0);
}

void UHIMainMenu::HIGraphicsButton()
{
    //settingsSwitcher->SetActiveWidgetIndex(1);
}

void UHIMainMenu::HIInputSettingsButton()
{
    //settingsSwitcher->SetActiveWidgetIndex(2);
}

void UHIMainMenu::HIUIButton()
{
    //settingsSwitcher->SetActiveWidgetIndex(3);
}

void UHIMainMenu::HIUpdateButtonsIndex(int _operator)
{
    buttonsIndex += _operator;

    if (buttonsIndex > 4)
    {
        buttonsIndex = 4;
    }
    else if (buttonsIndex < 0)
    {
        buttonsIndex = 0;
    }
}

void UHIMainMenu::HIMenuNavigation()
{
    switch (buttonsIndex)
    {
    case 0:
        HIUnselectContinueButton();
        HIUnselectQuitButton();
        HIUnselectCreditsButton();
        HIUnselectPlaygroundButton();
        HISelectPlayButton();
        break;
    case 1:
        HIUnselectPlayButton();
        HIUnselectQuitButton();
        HIUnselectCreditsButton();
        HIUnselectPlaygroundButton();
        HISelectContinueButton();
        break;

    case 2:
        HIUnselectPlayButton();
        HIUnselectContinueButton();
        HIUnselectQuitButton();
        HIUnselectCreditsButton();
        HISelectPlaygroundButton();
        break;

    case 3:
        HIUnselectPlayButton();
        HIUnselectContinueButton();
        HIUnselectQuitButton();
        HIUnselectPlaygroundButton();
        HISelectCreditsButton();
        break;
    case 4:
		HIUnselectPlayButton();
		HIUnselectContinueButton();
        HIUnselectCreditsButton();
        HIUnselectPlaygroundButton();
		HISelectQuitButton();
		break;
    default:
        break;
    }
}

/*
FReply UHIMainMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    Super::NativeOnKeyDown(InGeometry, InKeyEvent);

    FKey customKey = InKeyEvent.GetKey();

    if (customKey.GetDisplayName().ToString() == TEXT("Gamepad D-pad Up") || customKey.GetDisplayName().ToString() == TEXT("Up"))
    {
        HIUpdateButtonsIndex(1);
        HIMenuNavigation();

        return FReply::Handled();
    }
    else if (customKey.GetDisplayName().ToString() == TEXT("Gamepad D-pad Down") || customKey.GetDisplayName().ToString() == TEXT("Down"))
    {
        HIUpdateButtonsIndex(-1);
        HIMenuNavigation();

        return FReply::Handled();
    }

    return FReply::Unhandled();
}*/
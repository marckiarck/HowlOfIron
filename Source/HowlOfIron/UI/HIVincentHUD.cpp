// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HIVincentHUD.h"
#include "Characters/VincentVolk/HIWerewolfAttributes.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Game/HIGameData.h"

void UHIVincentHUD::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UHIVincentHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UHIVincentHUD::Initialize()
{
	Super::Initialize();

	arrow->SetVisibility(ESlateVisibility::Hidden);

	return true;
}

void UHIVincentHUD::HIInitVariables(const  UHIWerewolfAttributes* _attributes)
{
	// Numbers of UI only visible on EDITOR
#if WITH_EDITOR
	health->SetVisibility(ESlateVisibility::Visible);
	rage->SetVisibility(ESlateVisibility::Visible);
	howlTextBlock->SetVisibility(ESlateVisibility::Visible);
#else
	health->SetVisibility(ESlateVisibility::Collapsed);
	rage->SetVisibility(ESlateVisibility::Collapsed);
	howlTextBlock->SetVisibility(ESlateVisibility::Collapsed);
#endif

	maxHealth = _attributes->GetmaxHealth();
	fhealth = _attributes->Gethealth();
	maxRage = 50256200.f;
	frage = _attributes->GetchargedValue();
	howl = _attributes->Gethowl();

	HICalculateHealthBar();
	HICalculateRageBar();
	HICalculateHowl();

	godMode->SetVisibility(ESlateVisibility::Collapsed);
	godMode->SetText(FText::FromString(TEXT("GOD MODE")));
	godMode->SetColorAndOpacity(FSlateColor(FLinearColor::Red));

	showFPSText->SetVisibility(ESlateVisibility::Collapsed);
	showFPSText->SetText(FText::FromString(TEXT("FPS")));

	debugBars->SetVisibility(ESlateVisibility::Collapsed);

}

void UHIVincentHUD::HIChangeHealth(float _health)
{
	fhealth = _health;
	HICalculateHealthBar();
}

void UHIVincentHUD::HIChangeHowlNum(float _howl)
{
	howl = FMath::Max(0.05f, _howl);
	HICalculateHowl();
}

void UHIVincentHUD::HIChangeRage(float _rage)
{
	frage = _rage;
	HICalculateRageBar();
}

void UHIVincentHUD::HICalculateHowl_Implementation()
{
	progressHowl = howl;
	howlTextBlock->HISetCustomText(FText::FromString(FString::FromInt(int(progressHowl))));
}

void UHIVincentHUD::HIFinishAlpha_Implementation()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("Lvl_BossFightSteelheart")), true);
	// UGameplayStatics::OpenLevel(this, FName(TEXT("MainMenu")), true);
}

void UHIVincentHUD::HISetMaxHealth(float _maxHealth)
{
	maxHealth = _maxHealth;
	HICalculateHealthBar();
}

void UHIVincentHUD::HISetMaxRage(float _maxRage)
{
	maxRage = _maxRage;
	HICalculateRageBar();
}

void UHIVincentHUD::sethealth(float _health)
{

}

void UHIVincentHUD::setrage(float _rage)
{

}

void UHIVincentHUD::setMissiontext(FString _MissionText)
{
	missionText->HISetCustomText(FText::FromString(_MissionText));
}

void UHIVincentHUD::setRequisittext(FString _ReqText)
{
	requisitesText->HISetCustomText(FText::FromString(_ReqText));
}

void UHIVincentHUD::SetGodMode(bool _godMode)
{
#if WITH_EDITOR
	godMode->SetVisibility((_godMode) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	health->SetVisibility((!_godMode) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
#endif
}

void UHIVincentHUD::HISetFPSVisibilityText(bool _validate)
{
	if (showFPSText)
	{
		showFPSText->SetVisibility((_validate) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void UHIVincentHUD::HIUpdateFPSMessage(float _fps)
{
    if (_fps < 20.f)
    {
        showFPSText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
    }
    else if (_fps >= 20.f && _fps < 40.f)
    {
        showFPSText->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
    }
    else if (_fps >= 40.f && _fps < 59.f)
    {
        showFPSText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
    }
    else if (_fps >= 59.f && _fps <= 60.f)
    {
        showFPSText->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));
    }

    int auxFPS = int(_fps);
    FText fpsCounter = FText::FromString(FString::FromInt(auxFPS));
    showFPSText->SetText(fpsCounter);

}

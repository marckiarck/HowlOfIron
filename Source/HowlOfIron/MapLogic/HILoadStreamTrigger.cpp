// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLogic/HILoadStreamTrigger.h"
#include <Kismet/GameplayStatics.h>
#include "Game/HIGameData.h"
#include <Engine/LevelStreaming.h>

AHILoadStreamTrigger::AHILoadStreamTrigger(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.DoNotCreateDefaultSubobject(FName("Sprite")))
{

}

//si el trigger es del tipo LOAD, carga mapas, si aun hay pantalla de carga, los visibiliza automaticamente.
//si el trigger es del tipo VISIBLE, visibiliza los mapas asociandos
void AHILoadStreamTrigger::HILoadSublevel()
{
	int lNum = LevelName.Num();
	UHIGameInstance* GI = Cast<UHIGameInstance>(GetGameInstance());

	for (int i = 0; i < lNum; ++i)
	{
		if (triggerType == LoadLevelTriggerType::LOAD)
		{
			FLatentActionInfo Info;
			if (i == lNum - 1)
			{
				Info.CallbackTarget = UHIGameData::HIGetGameManager();
				Info.ExecutionFunction = "OnLevelLoaded";
			}
			Info.UUID = i;
			Info.Linkage = i;

			if (GI->testing || UHIGameData::HIGetGameManager()->loadScreenWidget->GetVisibility() != ESlateVisibility::Hidden)
			{
				UGameplayStatics::LoadStreamLevel(UHIGameData::HIGetWerewolfWorld(), LevelName[i], true, false, Info);
			}
			else
			{
				UGameplayStatics::LoadStreamLevel(UHIGameData::HIGetWerewolfWorld(), LevelName[i], false, false, Info);
			}
		}
		else if (triggerType == LoadLevelTriggerType::VISIBLE)
		{
			ULevelStreaming* level = UGameplayStatics::GetStreamingLevel(GetWorld(), LevelName[i]);
			if (level)
			{
				level->SetShouldBeVisible(true);
			}
		}
	}
}

void AHILoadStreamTrigger::HIUnloadSublevel()
{
	int lNum = LevelName.Num();

	for (int i = 0; i < lNum; ++i)
	{
		if (triggerType == LoadLevelTriggerType::LOAD)
		{
			FLatentActionInfo Info;
			Info.CallbackTarget = UHIGameData::HIGetGameManager();
			Info.ExecutionFunction = "OnLevelUnloaded";
			Info.UUID = i;
			Info.Linkage = i;

			UGameplayStatics::UnloadStreamLevel(UHIGameData::HIGetWerewolfWorld(), LevelName[i], Info, false);
		}
		else if (triggerType == LoadLevelTriggerType::VISIBLE)
		{
			ULevelStreaming* level = UGameplayStatics::GetStreamingLevel(GetWorld(), LevelName[i]);
			level->SetShouldBeVisible(false);
		}
	}
}

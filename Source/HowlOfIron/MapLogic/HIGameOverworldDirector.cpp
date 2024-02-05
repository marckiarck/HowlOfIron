// Fill out your copyright notice in the Description page of Project Settings.


#include "HIGameOverworldDirector.h"
#include "../Characters/VincentVolk/HIWerewolf.h"
#include "../Game/HIGameData.h"
#include "MapLogic/HI_Requisit.h"


void UHIGameOverworldDirector::SetMission(UHIMission* _mission)
{
	if (!actualMission)
	{
		if (!_mission->oneTimeOnly)
		{
			_mission->oneTimeCompleted = false;
			actualMission = _mission;
			ShowMission();
		}
		else
		{
			if (!_mission->oneTimeCompleted)
			{
				actualMission = _mission;
				ShowMission();
			}
		}
	}
}

void UHIGameOverworldDirector::ShowMission()
{
	AHIWerewolf* wolf = UHIGameData::HIGetPlayerWerewolf();

	if (actualMission)
	{
		if (wolf->widgetref)
		{
			wolf->widgetref->setMissiontext(actualMission->description);
		}
		int num = actualMission->requisits.Num();

		if (actualMission->sequenced)
		{
			for (int i = 0; i < num; ++i)
			{
				if (!actualMission->requisits[i].completed)
				{
					wolf->widgetref->setRequisittext(actualMission->requisits[i].description + " "
						+ FString::FromInt(actualMission->requisits[i].completionPercentage) + "/"
						+ FString::FromInt(actualMission->requisits[i].completionNum));
					break;
				}
			}
		}
		else
		{
			FString texto;

			for (int i = 0; i < num; ++i)
			{
				texto = texto +
					actualMission->requisits[i].description + " "
					+ FString::FromInt(actualMission->requisits[i].completionPercentage) + "/"
					+ FString::FromInt(actualMission->requisits[i].completionNum) + "\n";

			}

			if (wolf->widgetref)
			{
				wolf->widgetref->setRequisittext(texto);
			}
		}
	}
	else
	{
		if (wolf->widgetref)
		{
			wolf->widgetref->setMissiontext("");
			wolf->widgetref->setRequisittext("");
		}
	}
}

void UHIGameOverworldDirector::CompletedRequisitMission(MissionReq _reqEnum)
{
	if (actualMission)
	{
		int requListNum = actualMission->requisits.Num();

		for (int i = 0; i < requListNum; ++i)
		{
			if (!actualMission->requisits[i].completed)
			{
				if (_reqEnum == actualMission->requisits[i].missionType)
				{
					ExecuteReq(i);
				}

				if (actualMission->sequenced)
				{
					break;
				}
			}
		}

		ShowMission();

		for (int i = 0; i < requListNum; ++i)
		{
			if (!actualMission->requisits[i].completed)
			{
				return;
			}
		}

		Endmission();
	}
}

void UHIGameOverworldDirector::ResetMission()
{
	if (actualMission)
	{
		int requListNum = actualMission->requisits.Num();

		for (int i = 0; i < requListNum; ++i)
		{
			actualMission->requisits[i].completed = false;
			actualMission->requisits[i].completionPercentage = 0;
		}
	}
}

void UHIGameOverworldDirector::Endmission()
{
	ResetMission();
	if (actualMission->oneTimeOnly)
	{
		actualMission->oneTimeCompleted = true;
	}
	actualMission = nullptr;
	ShowMission();
}

void UHIGameOverworldDirector::StartCinematic()
{
}

void UHIGameOverworldDirector::EndCinematic()
{
}

void UHIGameOverworldDirector::ExecuteReq(int i)
{
	actualMission->requisits[i].completionPercentage++;

	if (actualMission->requisits[i].completionPercentage == actualMission->requisits[i].completionNum)
	{
		actualMission->requisits[i].completed = true;
		ShowMission();
	}
}

void UHIGameOverworldDirector::OnLevelLoaded()
{
	levelPrepared = true;
}

void UHIGameOverworldDirector::OnLevelUnloaded()
{


}

void UHIGameOverworldDirector::HideLoadScreen()
{
	FGameplayTagContainer bloquedImputTags;
	GET_BLOCK_INPUT_TAGS(bloquedImputTags);
	UHIGameData::HIGetPlayerWerewolf()->GetAbilitySystemComponent()->RemoveLooseGameplayTags(bloquedImputTags);
	UHIGameData::HIGetPlayerWerewolf()->GetCapsuleComponent()->SetSimulatePhysics(false);

	if (UHIGameData::HIGetGameManager()->loadScreenWidget)
	{
		UHIGameData::HIGetGameManager()->loadScreenWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	levelPrepared = false;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/VoiceActors/HIVoiceActorManager.h"
#include <Engine/DataTable.h>

TMap<FString, FName> UHIVoiceActorManager::voiceLinesHistoric = TMap<FString, FName>();

FName UHIVoiceActorManager::HIGetRandomDatatableRowName(UDataTable* datatable, VoiceDatatableCharType charType, VoiceDatatableNamesType nameType, VoiceDatatableCategoryType categoryType)
{
	FString rowNameExpresion = UHIVoiceActorManager::HIGetCharTypeString(charType);

	if (charType != WEREWOLF)
	{
		rowNameExpresion.Append(UHIVoiceActorManager::HIGetNameTypeString(nameType));
	}

	rowNameExpresion.Append(UHIVoiceActorManager::HIGetCategoryTypeString(categoryType));

	return HIGetRandomMatchingRow(datatable, rowNameExpresion);
}

FName UHIVoiceActorManager::HIGetRandomMatchingRow(UDataTable* datatable, FString rowNameExpresion)
{
	TArray<FName> matchingRows = HIGetMatchingRows(datatable, rowNameExpresion);


	ensureMsgf(matchingRows.Num() != 0, TEXT("Matching Rows Not Finded"));

	FName returnedFname = FName(matchingRows[FMath::RandRange(0, matchingRows.Num() - 1)]);
	if (voiceLinesHistoric.Contains(rowNameExpresion))
	{
		while (voiceLinesHistoric[rowNameExpresion].IsEqual(returnedFname) == true)
		{
			returnedFname = FName(matchingRows[FMath::RandRange(0, matchingRows.Num() - 1)]);
		};


	}

	voiceLinesHistoric.Add(rowNameExpresion, returnedFname);

	return returnedFname;
}

TArray<FName> UHIVoiceActorManager::HIGetMatchingRows(UDataTable* datatable, FString rowNameExpresion)
{
	TArray<FName> rowNames = datatable->GetRowNames();
	TArray<FName> matchingRows;

	for (FName rowNameIter : rowNames)
	{
		FString rowNameString;
		rowNameIter.ToString(rowNameString);

		if (rowNameString.Contains(rowNameExpresion))
		{
			matchingRows.Add(rowNameIter);
		}

	}

	return matchingRows;
}

FName UHIVoiceActorManager::HIGetRandomCharacterDatatableRowName(UDataTable* datatable, AHIAbilityCharacter* target, VoiceDatatableCategoryType categoryType)
{
	FString rowNameExpresion = target->HIGetVoiceString();
	rowNameExpresion.Append(UHIVoiceActorManager::HIGetCategoryTypeString(categoryType));

	return HIGetRandomMatchingRow(datatable, rowNameExpresion);
}

FName UHIVoiceActorManager::HIGetDatatableRowName(UDataTable* datatable, VoiceDatatableCharType charType, VoiceDatatableNamesType nameType, VoiceDatatableCategoryType categoryType, int voiceLineNumber, int voiceLineVariant)
{
	FString rowNameExpresion = UHIVoiceActorManager::HIGetCharTypeString(charType);

	if (charType != WEREWOLF)
	{
		rowNameExpresion.Append(UHIVoiceActorManager::HIGetNameTypeString(nameType));
	}

	rowNameExpresion.Append(UHIVoiceActorManager::HIGetCategoryTypeString(categoryType));

	rowNameExpresion.Append("_");
	rowNameExpresion.Append(FString::FromInt(voiceLineNumber));

	rowNameExpresion.Append("_");
	rowNameExpresion.Append(FString::FromInt(voiceLineVariant));

	return FName(rowNameExpresion);
}

FName UHIVoiceActorManager::HIGetDatatableCharacterRowName(UDataTable* datatable, AHIAbilityCharacter* target, VoiceDatatableCategoryType categoryType, int voiceLineNumber, int voiceLineVariant)
{
	FString rowNameExpresion = target->HIGetVoiceString();

	rowNameExpresion.Append(UHIVoiceActorManager::HIGetCategoryTypeString(categoryType));

	rowNameExpresion.Append("_");
	rowNameExpresion.Append(FString::FromInt(voiceLineNumber));

	rowNameExpresion.Append("_");
	rowNameExpresion.Append(FString::FromInt(voiceLineVariant));

	return FName(rowNameExpresion);
}

FString UHIVoiceActorManager::HIGetCharTypeString(VoiceDatatableCharType charType)
{
	switch (charType)
	{
	case HUNTER:
	{
		return FString(TEXT("HU"));
	};
	break;
	case  MUTTON:
	{
		return FString(TEXT("MU"));
	};
	break;
	case WEREWOLF:
	{
		return FString(TEXT("WW"));
	};
	break;
	case OWLMAN:
	{
		return FString(TEXT("OW"));
	}
	default:
	{
		return FString(TEXT("MU"));
	};
	break;
	}
}

FString UHIVoiceActorManager::HIGetNameTypeString(VoiceDatatableNamesType nameType)
{
	FString returnedString;
	VOICE_ACTORS_CASE(nameType, returnedString);
	
	return returnedString;
}

FString UHIVoiceActorManager::HIGetCategoryTypeString(VoiceDatatableCategoryType categoryType)
{
	switch (categoryType)
	{
	case COMBAT_VOICE:
	{
		return TEXT("_combat");
	};
	break;
	case ATTACK:
	{
		return TEXT("_Attack");
	};
	break;
	case ALERT:
	{
		return TEXT("_alert");
	};
	case DAMAGED :
	{
		return TEXT("_Damaged");
	}
	break;
	case EXCLUSIVE :
	{
		return TEXT("_Exclusive");
	};
	break;
	case  FEAR :
	{
		return TEXT("_Fear");
	};
	break;
	case  CONVERSATION :
	{
		return TEXT("_Conversation");
	};
	break;
	case SEARCH :
	{
		return TEXT("_Search");
	};
	break;
	case DEATH :
	{
		return TEXT("_Death");
	};
	break;
	case GRUNT_LIGHT :
	{
		return TEXT("_Grunt_Light");
	};
	break;
	case  GRUNT_HARD :
	{
		return TEXT("_Grunt_Hard");
	};
	break;
	case  HOWL :
	{
		return TEXT("_Howl");
	}
	default:
	{
		return TEXT("_combat");
	}
	}
}

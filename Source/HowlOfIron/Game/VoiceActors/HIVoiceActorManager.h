// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <UObject/SoftObjectPtr.h>
#include <Characters/HIAbilityCharacter.h>
#include <Characters/Enemies/HIEnemy.h>
#include "HIVoiceActorManager.generated.h"

UENUM()
enum VoiceDatatableCategoryType {
	COMBAT_VOICE,
	ATTACK,
	ALERT,
	DAMAGED,
	EXCLUSIVE,
	FEAR,
	CONVERSATION,
	SEARCH,
	DEATH,
	GRUNT_LIGHT,
	GRUNT_HARD,
	HOWL
};

UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API UHIVoiceActorManager : public UObject
{
	GENERATED_BODY()

private:
	static UPROPERTY(Transient) TMap<FString, FName> voiceLinesHistoric;

public:
	UFUNCTION(BlueprintPure)
		static FName HIGetRandomDatatableRowName(UDataTable* datatable, VoiceDatatableCharType charType, VoiceDatatableNamesType nameType, VoiceDatatableCategoryType categoryType);

	UFUNCTION(BlueprintPure)
		static FName HIGetRandomCharacterDatatableRowName(UDataTable* datatable, AHIAbilityCharacter* target, VoiceDatatableCategoryType categoryType);

	UFUNCTION(BlueprintPure)
		static FName HIGetDatatableRowName(UDataTable* datatable, VoiceDatatableCharType charType, VoiceDatatableNamesType nameType, VoiceDatatableCategoryType categoryType, int voiceLineNumber, int voiceLineVariant);

	UFUNCTION(BlueprintPure)
		static FName HIGetDatatableCharacterRowName(UDataTable* datatable, AHIAbilityCharacter* target, VoiceDatatableCategoryType categoryType, int voiceLineNumber, int voiceLineVariant);

private:
	static FString HIGetCharTypeString(VoiceDatatableCharType charType);
	static FString HIGetNameTypeString(VoiceDatatableNamesType nameType);
	static FString HIGetCategoryTypeString(VoiceDatatableCategoryType categoryType);
	static TArray<FName> HIGetMatchingRows(UDataTable* datatable, FString rowNameExpresion);
	static FName HIGetRandomMatchingRow(UDataTable* datatable, FString rowNameExpresion);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Game/Conditions/HICondition.h>
#include "HILevelLoadContext.generated.h"

UENUM()
enum LoadConditionCheckMode {
	MEET_ANY_CONDITION,
	MEET_ALL_CONDITIONS
};

UCLASS(editinlinenew, DefaultToInstanced, BlueprintType, Blueprintable)
class HOWLOFIRON_API UHILevelLoadContext : public UObject
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Context")
		TEnumAsByte<LoadConditionCheckMode> conditonCheckMode = MEET_ALL_CONDITIONS;

	UPROPERTY(EditAnywhere, Category = "Context")
		FName LevelToLoad;

	UPROPERTY(EditAnywhere, Instanced, Category = "Conditions")
		TArray<UHICondition*> conditionsToLoadLevel;

	UPROPERTY()
		bool levelLoaded;

public:

	UFUNCTION()
	void HIInitilaize();

	UFUNCTION()
		void HITryLoadLevel();

private:
	UFUNCTION()
		bool HIMeetAllConditions();

	UFUNCTION()
		bool HIMeetAnyCondition();
};

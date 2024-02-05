// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "HILoadStreamTrigger.generated.h"

UENUM(BlueprintType)
enum class LoadLevelTriggerType : uint8
{
	LOAD = 0 UMETA(DisplayName = "LOAD"),
	VISIBLE = 1  UMETA(DisplayName = "VISIBLE"),
};

UCLASS()
class HOWLOFIRON_API AHILoadStreamTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		LoadLevelTriggerType triggerType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FName> LevelName;

public:
	AHILoadStreamTrigger(const FObjectInitializer& ObjectInitializer);


	UFUNCTION(BlueprintCallable)
		void HILoadSublevel();

	UFUNCTION(BlueprintCallable)
		void HIUnloadSublevel();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HICineCamera.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API AHICineCamera : public AActor
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
		void BeforeScriptedCamera();

	UFUNCTION(BlueprintImplementableEvent)
		void BeginScriptedCamera();

	UFUNCTION(BlueprintImplementableEvent)
		void EndScriptedCamera();
};

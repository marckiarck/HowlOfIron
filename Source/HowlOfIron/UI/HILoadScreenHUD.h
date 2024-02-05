// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HILoadScreenHUD.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHILoadScreenHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:

	UPROPERTY()
		float timer = 0;

	UPROPERTY()
		bool sceneReady = false;

public:
	UFUNCTION(BlueprintCallable)
		void LoadSceneAsync();

	UFUNCTION(BlueprintCallable)
		void ChangeScene();
};

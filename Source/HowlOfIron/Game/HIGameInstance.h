// @AUTHOR: Guillermo Su�rez

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../MapLogic/HIGameOverworldDirector.h"
#include <UI/Tooltips/HITooltipData.h>
#include "HIGameInstance.generated.h"

class AHISpeaker;

UCLASS()
class HOWLOFIRON_API UHIGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UHIGameInstance(const FObjectInitializer& ObjectInitializer);

public:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UHIGameOverworldDirector* gameManager;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UHIGameOverworldDirector> gameManagerType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool testing = true;

	UPROPERTY(Transient)
		UHITooltipWidget* tooltipWidget;

#pragma region PAUSE_MENU_SCREEN_RESOLUTION

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Screen Resolution")
		TArray<FText> screenResolutionChoices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Screen Resolution")
		int screenResolutionIndex;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Screen Resolution")
		bool screenResolutionBool;

#pragma endregion
#pragma region PAUSE_MENU_WINDOW_TYPE

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Window Type")
		TArray<FText> windowTypeChoices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Window Type")
		int windowTypeIndex;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Window Type")
		bool windowTypeBool;

#pragma endregion
#pragma region PAUSE_MENU_BRIGHTNESS

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Brightness")
		TArray<FText> brightnessChoices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Brightness")
		int brightnessIndex;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Brightness")
		bool brightnessBool;

#pragma endregion
#pragma region PAUSE_MENU_QUALITY

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Quality")
		TArray<FText> qualityChoices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Quality")
		int qualityIndex;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | Graphics | Quality")
		bool qualityBool;

#pragma endregion
#pragma region PAUSE_MENU_SOUND

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PauseMenu | Sound")
		float generalSoundValue = .5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PauseMenu | Sound")
		float sfxValue = .5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PauseMenu | Sound")
		float voicesValue = .5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PauseMenu | Sound")
		float ambientValue = .5f;

#pragma endregion

#pragma region PAUSE_MENU_UI
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | UI | Subtitles")
		TArray<FText> subtitleChoices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | UI | Subtitles")
		int subtitlesIndex;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | UI | Subtitles")
		bool subtitlesBool;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | UI | Colorbind")
		TArray<FText> colorbindChoices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | UI | Colorbind")
		int colorbindIndex;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PauseMenu | UI | Colorbind")
		bool colorbindBool;

#pragma endregion

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AxisActions | Sensivility")
		float mouseSensivility = 25.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AxisActions | Camera Axis")
		int reverseYCamera = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AxisActions | Camera Axis")
		int reverseXCamera = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AxisActions | Camera Axis")
		int reverseCameraIndex = 0;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AxisActions | Show FPS")
        int showFPSIndex = 0;

protected:


private:
	UPROPERTY(EditAnywhere, Category = "Tooltips", meta = (RequiredAssetDataTags = "RowStructure=HIVideoDataTable"))
		class UDataTable* tooltipsDataTabe;

	UPROPERTY(Transient)
		TMap<FName, UHITooltipData*> tooltipDataArray;


public:
	UFUNCTION(BlueprintImplementableEvent)
	void HIShowTooltip(FName rowName);

	UFUNCTION(BlueprintCallable)
		UHITooltipWidget* HIGetTooltipWidget();

protected:


private:

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void HIActivateTooltip(FName rowName);
};

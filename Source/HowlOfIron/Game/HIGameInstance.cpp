// @AUTHOR: Guillermo Suárez


#include "Game/HIGameInstance.h"
#include "HIGameData.h"
#include <Engine/DataTable.h>
#include "Math/UnrealMathUtility.h"
#include <UI/Tooltips/HITooltipWidget.h>
#include "../UI/Tooltips/HIVideoDataTable.h"
#include <MapLogic/HIObjectPooler_Actors.h>


UHIGameInstance::UHIGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UHIGameInstance::HIActivateTooltip(FName rowName)
{

	FString ensureMessage = TEXT("Row doesnt exist in tooltip datatble: ");
	ensureMessage.Append(rowName.ToString());
	ensureMsgf(tooltipDataArray.Contains(rowName), TEXT("Row doesnt exist in tooltip datatble"));

	
	tooltipWidget->tooltipData->HICopyTooltipData(tooltipDataArray[rowName]);

	tooltipWidget->HIShow();
}

UHITooltipWidget* UHIGameInstance::HIGetTooltipWidget()
{
	return tooltipWidget;
}

void UHIGameInstance::Init()
{
	Super::Init();

	if (!gameManager)
	{
		gameManager = gameManagerType.GetDefaultObject();
		UHIGameData::HISetGameManager(gameManager);
	}


	UHIGameData::HIClearStaticReferences();
	UHIGameData::HISetStaticEffect(NewObject<UGameplayEffect>());
	AHIObjectPooler_Actors::HIResetObjectPooler();

	FString ContextString = TEXT("Data table context");
	FHIVideoDataTable* Row = nullptr;
	TArray<FName> RowNames = tooltipsDataTabe->GetRowNames();

	for (FName rowName : RowNames)
	{
		Row = tooltipsDataTabe->FindRow<FHIVideoDataTable>(rowName, ContextString, true);

		UHITooltipData* rowTooltip = NewObject<UHITooltipData>();
		rowTooltip->tooltipTitle = Row->tooltipTitle;
		rowTooltip->customTooltipTextStruct = Row->customTooltipTextStruct;
		rowTooltip->sizeY = Row->sizeY;
		rowTooltip->videoToPlay = Row->VideoToPlay;

		tooltipDataArray.Add(rowName, rowTooltip);
	}

	UHIGameData::HISetGameInstance(this);
}

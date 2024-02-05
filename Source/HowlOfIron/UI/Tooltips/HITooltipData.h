// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HITooltipData.generated.h"

USTRUCT(BlueprintType)
struct FTooltipText
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
		FText pc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
		FText xbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
		FText playstation;
};

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHITooltipData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		FString tooltipTitle = FString(TEXT("Instanced"));

	UPROPERTY(BlueprintReadOnly)
		FTooltipText customTooltipTextStruct;

	UPROPERTY(BlueprintReadOnly)
		float sizeY;

	UPROPERTY(BlueprintReadOnly)
		class UMediaSource* videoToPlay = nullptr;

public:
	void HICopyTooltipData(UHITooltipData* otherTooltip);
	
};

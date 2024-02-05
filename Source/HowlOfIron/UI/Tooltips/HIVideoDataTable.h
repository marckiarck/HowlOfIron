// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include <MediaAssets/Public/MediaSource.h>
#include "HIVideoDataTable.generated.h"

/**
 *
 */
USTRUCT()
struct HOWLOFIRON_API FHIVideoDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString tooltipTitle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FTooltipText customTooltipTextStruct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float sizeY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UMediaSource* VideoToPlay = nullptr;
};

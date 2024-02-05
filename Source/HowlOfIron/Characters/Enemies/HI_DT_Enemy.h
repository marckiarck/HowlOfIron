// Created By pablo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HI_DT_Enemy.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct HOWLOFIRON_API FHI_DT_Enemy : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FHI_DT_Enemy();
	~FHI_DT_Enemy() {};

	// Points per second to decrease to the detectionMeter
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float decreaseDetectionPerSecond = 20.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ToolTip = "Distance To Navlink-Werewolf to throw grenade"))
		float launchGrenadeRadious = 500.f;
};
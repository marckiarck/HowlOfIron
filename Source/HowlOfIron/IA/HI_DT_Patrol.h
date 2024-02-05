// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HI_DT_Patrol.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct HOWLOFIRON_API FHI_DT_Patrol : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FHI_DT_Patrol() {};
	~FHI_DT_Patrol() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float frequencyShootbase = 3;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxShootDistance = 1900.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int maxEnemiesShooting = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int maxEnemiesFirstRing = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int maxEnemiesSecondRing = 4;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float chanceDodge = 0.6f;


};

// Created By pablo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HI_DT_MasSec.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct HOWLOFIRON_API FHI_DT_MasSec : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FHI_DT_MasSec() {};
	~FHI_DT_MasSec() {};

	UPROPERTY(EditAnywhere)
		TArray<UClass*> TypesOfEnemies;
};

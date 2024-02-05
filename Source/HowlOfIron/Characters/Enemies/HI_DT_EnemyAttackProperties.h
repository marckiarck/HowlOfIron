// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HI_DT_EnemyAttackProperties.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct HOWLOFIRON_API FHI_DT_EnemyAttackProperties : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	//Time the enemy is going to be preparing it shoot attack
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float attackDelay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float attackDuration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float attackRange = 2000.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float attackAngle = 20.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float attackDamage = 20.f;
};
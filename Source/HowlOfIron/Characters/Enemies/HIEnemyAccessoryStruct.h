// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "Game/HIGameData.h"
#include "HIWeaponConditionStruct.h"
#include "HIEnemyAccessoryStruct.generated.h"

USTRUCT(BlueprintType)
struct FHIEnemyAccessoryStruct
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (GetOptions = "HIGetEnemyAccessoriesRowNames"))
		FName accessoryName;

	/// <summary>
	/// Weapon condition to change to it in the BHV Tree (NONE by default)
	/// </summary>
	UPROPERTY(EditAnywhere, meta = (Tooltip = "(Only for weapons)"))
		FHIWeaponConditionStruct weaponCondition;

private:
	TArray<FName> HIGetEnemyAccessoriesRowNames()
	{
		return UHIGameData::HIGetEnemyAccessoriesRowNames();
	}
};

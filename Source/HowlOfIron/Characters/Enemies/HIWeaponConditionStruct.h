// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "HIWeaponConditionStruct.generated.h"

UENUM()
enum WeaponConditionType {
	NO_CONDITION = 0, // By default
	DISTANCE_TO_WEREWOLF,
	INVULNERABILITY_STATUS
};

UENUM()
enum DistComparisonType {
	EQUALS,
	LESS_THAN,
	MORE_THAN,
	LESS_EQUAL,
	MORE_EQUAL,
	BETWEEN
};

USTRUCT(BlueprintType)
struct FHIWeaponConditionStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TEnumAsByte<WeaponConditionType> conditionType = WeaponConditionType::NO_CONDITION;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "conditionType == WeaponConditionType::DISTANCE_TO_WEREWOLF", EditConditionHides))
		TEnumAsByte<DistComparisonType> comparisonType;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "conditionType == WeaponConditionType::DISTANCE_TO_WEREWOLF && comparisonType != DistComparisonType::BETWEEN", EditConditionHides))
		float distance;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "conditionType == WeaponConditionType::DISTANCE_TO_WEREWOLF && comparisonType == DistComparisonType::BETWEEN", EditConditionHides))
		float minorDistance;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "conditionType == WeaponConditionType::DISTANCE_TO_WEREWOLF && comparisonType == DistComparisonType::BETWEEN", EditConditionHides))
		float mayorDistance;
};

#pragma once


#include "CoreMinimal.h"
#include "HIBaseDataTable.h"
#include "HIWerewolfDatatable.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct HOWLOFIRON_API FHI_WerewolfDatatable : public FHI_BaseDataTable
{
	GENERATED_USTRUCT_BODY()



	// Distance at which the werewolf will be able to jump to a wall to climb from the floor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing", meta = (ClampMin = "0.0", ClampMax = "5000.0", UIMin = "0.0", UIMax = "5000.0"))
		float distanceToWallToClimbFromFloor = 700.f;


	// Distance at which the werewolf will be able to jump to a wall to climb from a building
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing", meta = (ClampMin = "0.0", ClampMax = "5000.0", UIMin = "0.0", UIMax = "5000.0"))
		float distanceToWallToClimbFromBuilding = 1900.f;

	// Speed at which the werewolf will climb
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing", meta = (ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
		float climbingSpeed = 750.f;


	// Distance to the borders of a building at which the werewolf will be able to jump to another building or to execute an enemy from above
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump", meta = (ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
		float distanceToBordersToJump = 150.f;

	// Distance to the building we want to jump (jump between buildings)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float distanceToBuildingToJump = 1900.f;

	// Array with the angles (in Z axis with the camera) to the building we want to jump. Check first angle, if not hit, check second, ...
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump", meta = (ClampMin = "0.0", ClampMax = "180.0", UIMin = "0.0", UIMax = "180.0"))
		TArray<float> anglesToBuildingToJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump", meta = (ClampMin = "0.0", ClampMax = "500000.0", UIMin = "0.0", UIMax = "180.0"))
		float jumpVelocity = 1200.f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Finisher", meta = (ClampMin = "0.0", ClampMax = "5000.0", UIMin = "0.0", UIMax = "5000.0"))
		float capsuleRadius = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Finisher", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float capsuleHeight = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Finisher", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float finisherJumpVelocity = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Finisher", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float fearSphereRadious = 500.f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Execution", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float executionJumpVelocity = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Execution", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float executionFearSphereRadious = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Execution", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float sameLevelExecutionDistance = 200.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Execution", meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "10000.0"))
        float finisherThreshold = 50.f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float dashDistance = 700;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float dashDuration = 0.45f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Howl", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float howlRadio = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Healing", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
        float healingPerSeconds = 20.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Healing", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
        float startHealingHP = 125.f;

};

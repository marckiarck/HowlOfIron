// @AUTHOR: Guille, Carlos

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HIWall.generated.h"

UCLASS()
class HOWLOFIRON_API AHIWall : public AActor
{
	GENERATED_BODY()

public:
	AHIWall();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
		USceneComponent* sceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
		class UBoxComponent* boxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
		class USplineComponent* climbingSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
		class UArrowComponent* arrowComponent;
	
	// Separation of the wall to which we want to put the spline. This is to make the climbing correct
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall|Climbing")
		float splineSeparation;

	// It specifies if the wall is climbable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall|Climbing")
		bool isClimbable;

	// Min distance from the borders (top and bottom of the wall) that we want to start climbing. If we are looking at the top of the wall, the jump target position height will be 'top of the wall - climbMinDistanceFromBorders'.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall|Climbing")
		float climbMinDistanceFromBorders;



public:
	// Function to reload the wall components and recalculate spline
	UFUNCTION(BlueprintCallable)
		void HIReload();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

};

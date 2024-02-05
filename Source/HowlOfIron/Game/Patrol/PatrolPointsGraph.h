// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HIPatrolPoint.h"
#include "PatrolPointsGraph.generated.h"

#define  distanceMatrixRow TMap<AHIPatrolPoint*, float>
#define  MinimumPathMatrixRow TMap<AHIPatrolPoint*, AHIPatrolPoint*>

UCLASS()
class HOWLOFIRON_API UPatrolPointsGraph : public UObject
{
	GENERATED_BODY()

private:
	TMap<AHIPatrolPoint*, distanceMatrixRow> adjacencyMatrix;
	TMap<AHIPatrolPoint*, distanceMatrixRow> minimumDistanceMatrix;
	TMap<AHIPatrolPoint*, MinimumPathMatrixRow> minimumPathMatrix;
	TArray<AHIPatrolPoint*> graphPatrolPointsArray;

public:
	void HIInitializePatrolPoints(TArray<AHIPatrolPoint*> graphPatrolPoints);

	/// <summary>
	/// Returns the waypoint in the minimum path to go from the initial patrol point to the target patrol point
	/// </summary>
	/// <param name="initialPatrolPoint"> stating patrol point </param>
	/// <param name="targetPatrolPoint"> target patrol point </param>
	/// <returns></returns>
	UFUNCTION()
	AHIPatrolPoint* HIGetMinimumPathPatrolPoint(AHIPatrolPoint* initialPatrolPoint, AHIPatrolPoint* targetPatrolPoint);

private:
#pragma region FLOYD_ALGORITHMS_FUNCTIONS
	void HIInitializeMatrixes(TArray<AHIPatrolPoint*> graphPatrolPoints);
	void HICalculateMinimumPaths();
#pragma endregion
};

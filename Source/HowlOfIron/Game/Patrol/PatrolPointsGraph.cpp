// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Patrol/PatrolPointsGraph.h"

void UPatrolPointsGraph::HIInitializePatrolPoints(TArray<AHIPatrolPoint*> graphPatrolPoints)
{
	HIInitializeMatrixes(graphPatrolPoints);
	HICalculateMinimumPaths();
}

AHIPatrolPoint* UPatrolPointsGraph::HIGetMinimumPathPatrolPoint(AHIPatrolPoint* initialPatrolPoint, AHIPatrolPoint* targetPatrolPoint)
{
	AHIPatrolPoint* substitutePatrolPoint = initialPatrolPoint->UpdateRequieredPatrolPoint();

	if (substitutePatrolPoint == nullptr)
	{
		return minimumPathMatrix[initialPatrolPoint][targetPatrolPoint];
	}else{
		return substitutePatrolPoint;
	}
	
}

void UPatrolPointsGraph::HIInitializeMatrixes(TArray<AHIPatrolPoint*> graphPatrolPoints)
{
	graphPatrolPointsArray = graphPatrolPoints;

	for (AHIPatrolPoint* patrolPoint : graphPatrolPoints)
	{
		distanceMatrixRow adjacencyMatrixRow;
		MinimumPathMatrixRow minimumPathMatrixRow;

		adjacencyMatrix.Add(patrolPoint, adjacencyMatrixRow);
		minimumPathMatrix.Add(patrolPoint, minimumPathMatrixRow);

		for (AHIPatrolPoint* neigbourPatrolPoint : graphPatrolPoints)
		{
			if (neigbourPatrolPoint == patrolPoint)
			{
				adjacencyMatrix[patrolPoint].Add(neigbourPatrolPoint, 0.f);
				minimumPathMatrix[patrolPoint].Add(neigbourPatrolPoint, neigbourPatrolPoint);
			}
			else {

				//AdjacencyMatrix creation
				if (patrolPoint->HIGetNeighbours().Contains(neigbourPatrolPoint))
				{
					adjacencyMatrix[patrolPoint].Add(neigbourPatrolPoint, abs(FVector::DistSquared(patrolPoint->GetActorLocation(), neigbourPatrolPoint->GetActorLocation())));
				}
				else {
					adjacencyMatrix[patrolPoint].Add(neigbourPatrolPoint, MAX_FLT);
				}

				//MinimumPathMatrix creation
				if (patrolPoint->HIGetNeighbours().Contains(neigbourPatrolPoint))
				{
					minimumPathMatrix[patrolPoint].Add(neigbourPatrolPoint, neigbourPatrolPoint);
				}
				else {
					minimumPathMatrix[patrolPoint].Add(neigbourPatrolPoint, nullptr);
				}
			}			
		}
	}

	minimumDistanceMatrix = adjacencyMatrix;
}

void UPatrolPointsGraph::HICalculateMinimumPaths()
{

	for (AHIPatrolPoint* k : graphPatrolPointsArray)
	{
		for (AHIPatrolPoint* i : graphPatrolPointsArray)
		{
			for (AHIPatrolPoint* j : graphPatrolPointsArray)
			{
				float compositedMinimumDistance = minimumDistanceMatrix[i][k] + minimumDistanceMatrix[k][j];
				if (minimumDistanceMatrix[i][j] > compositedMinimumDistance)
				{
					minimumDistanceMatrix[i][j] = compositedMinimumDistance;
					minimumPathMatrix[i][j] = minimumPathMatrix[i][k];
				}
			}
		}
	}
}
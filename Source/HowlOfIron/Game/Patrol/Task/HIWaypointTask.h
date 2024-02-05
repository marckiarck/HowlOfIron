// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HIWaypointTask.generated.h"

class AHIEnemy;
class AHIPatrolPoint;

/**
 * 
 */
UCLASS(editinlinenew, DefaultToInstanced, BlueprintType, Blueprintable)
class HOWLOFIRON_API UHIWaypointTask : public UObject
{
	GENERATED_BODY()


	
public:

protected:
	UPROPERTY(Transient)
	AHIEnemy* enemy;

	UPROPERTY(Transient)
	AHIPatrolPoint* waypoint;
private:

	bool executingTask = false;

	

public:

	UFUNCTION()
		virtual void  HIStartTask(AHIEnemy* _enemy, AHIPatrolPoint* _waypoint);

	UFUNCTION()
		virtual void HIUpdateTask(float DeltaTime);

	UFUNCTION()
		virtual void HIEndTask();


	UFUNCTION()
	virtual void HIAbortTask();


	UFUNCTION()
	bool HIIsExecuting();

protected:

private:
	
};

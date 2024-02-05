// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HIComponentVisualizer.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HOWLOFIRON_API UHIComponentVisualizer : public UActorComponent
{
	GENERATED_BODY()

public:
	UHIComponentVisualizer() {};

	UPROPERTY(EditAnywhere)
		FColor drawColor = FColor::Blue;
};

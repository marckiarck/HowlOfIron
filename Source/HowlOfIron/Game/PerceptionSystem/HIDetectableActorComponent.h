// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HIDetectableActorComponent.generated.h"

#define DETECTABLE_ACTORS UHIDetectableActorsArray::HIGetDetectableActors()

UCLASS(BlueprintType)
class HOWLOFIRON_API UHIDetectableActorsArray : public UObject
{
	GENERATED_BODY()

private:
	static UPROPERTY() TArray<UHIDetectableActorComponent*> detectableActorsArray;

public:
	static void HIAddDetectableActor(UHIDetectableActorComponent* detectableActor);
	static void HIRemoveDetectableActor(UHIDetectableActorComponent* detectableActor);
	static TArray<AActor*> HIGetDetectableActors();
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOWLOFIRON_API UHIDetectableActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHIDetectableActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
};

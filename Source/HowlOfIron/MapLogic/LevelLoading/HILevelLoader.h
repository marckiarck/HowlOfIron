// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HILevelLoader.generated.h"

UCLASS()
class HOWLOFIRON_API AHILevelLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHILevelLoader();

private:
	UPROPERTY(EditAnywhere, Instanced, Category = "Level Load", meta = (DisplayName = "Level Load Conditions"))
	TArray<UHILevelLoadContext*> levelLoadContexts;

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

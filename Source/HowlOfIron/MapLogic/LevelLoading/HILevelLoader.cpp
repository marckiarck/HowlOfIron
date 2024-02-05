// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLogic/LevelLoading/HILevelLoader.h"

// Sets default values
AHILevelLoader::AHILevelLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHILevelLoader::BeginPlay()
{
	Super::BeginPlay();

	for (UHILevelLoadContext* iterLevelContext : levelLoadContexts)
	{
		iterLevelContext->HIInitilaize();
	}
}

// Called every frame
void AHILevelLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (UHILevelLoadContext* iterLevelContext : levelLoadContexts)
	{
		iterLevelContext->HITryLoadLevel();
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "HIMeshReplacer.h"

// Sets default values
AHIMeshReplacer::AHIMeshReplacer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AHIMeshReplacer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHIMeshReplacer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AHIMeshReplacer::ReplaceStaticMeshes() 
//{
//	for (TActorIterator<Aa> actorItr(GetWorld()); actorItr; ++actorItr)
//	{
//		UStaticMesh* staticMesh = *actorItr;
//		if (actor->ActorHasTag(ActorTag))
//			return actor;
//
//		//if(staticMesh->mesh)
//	}
//
//	return nullptr;
//}


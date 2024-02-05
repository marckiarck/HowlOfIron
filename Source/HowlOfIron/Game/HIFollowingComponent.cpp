// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HIFollowingComponent.h"

// Sets default values for this component's properties
UHIFollowingComponent::UHIFollowingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHIFollowingComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsToFind;

	UGameplayStatics::GetAllActorsOfClass(GetOwner()->GetWorld(), typeOfObjectToFollow, actorsToFind);


	if (actorsToFind.Num() != 0)
	{
		actorToFollow = actorsToFind[0];
	}

}


// Called every frame
void UHIFollowingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (actorToFollow)
	{
		GetOwner()->SetActorLocation(actorToFollow->GetActorLocation() + offset, false, nullptr, ETeleportType::None);
	}

}


// @AUTHOR: Germán López

#include "HICustomActor.h"

#pragma region UE_FUNCTIONS
AHICustomActor::AHICustomActor()
{
	PrimaryActorTick.bCanEverTick = false;


}



void AHICustomActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AHICustomActor::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion 


#pragma region CLASS_FUNCTIONS
void AHICustomActor::HISetActorName(AActor* actor, FString _name) 
{
	#if WITH_EDITOR
	actor->SetActorLabel(_name);
	#endif
}




void AHICustomActor::FinishPlacement() {
	this->K2_DestroyActor();
	GEngine->ForceGarbageCollection(true);
}


#pragma endregion
#include "Game/PerceptionSystem/HIDetectableActorComponent.h"
#include <AbilitySystemInterface.h>
#include <GameplayTagContainer.h>
#include <HIMacros.h>

TArray<UHIDetectableActorComponent*> UHIDetectableActorsArray::detectableActorsArray;

// Sets default values for this component's properties
UHIDetectableActorComponent::UHIDetectableActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHIDetectableActorComponent::BeginPlay()
{
	Super::BeginPlay();

	UHIDetectableActorsArray::HIAddDetectableActor(this);
}

void UHIDetectableActorComponent::BeginDestroy()
{
	Super::BeginDestroy();

	UHIDetectableActorsArray::HIRemoveDetectableActor(this);
}

void UHIDetectableActorsArray::HIAddDetectableActor(UHIDetectableActorComponent* detectableActor)
{
	detectableActorsArray.Add(detectableActor);
}

void UHIDetectableActorsArray::HIRemoveDetectableActor(UHIDetectableActorComponent* detectableActor)
{
	detectableActorsArray.Remove(detectableActor);
}

TArray<AActor*> UHIDetectableActorsArray::HIGetDetectableActors()
{
	TArray<AActor*> returnedDetectableActors;

	for (UHIDetectableActorComponent* detectableActor : detectableActorsArray)
	{
		IAbilitySystemInterface* detectableAbilityCharacter = Cast<IAbilitySystemInterface>(detectableActor->GetOwner());
		if (detectableAbilityCharacter)
		{
			FGameplayTagContainer abilityCharacterTags;
			detectableAbilityCharacter->GetAbilitySystemComponent()->GetOwnedGameplayTags(abilityCharacterTags);
			if (abilityCharacterTags.HasAny(FGameplayTagContainer(GET_GAMEPLAY_TAG(HIGHSTEAM_TAG))) == false)
			{
				returnedDetectableActors.Add(detectableActor->GetOwner());
			}
		}
		else {
			returnedDetectableActors.Add(detectableActor->GetOwner());
		}
	}

	return returnedDetectableActors;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "HIComboManagerComponent.h"

#include <Components/InputComponent.h>
#include <GameplayTagContainer.h>
#include "HIMacros.h"

UHIComboManagerComponent::UHIComboManagerComponent() : launchingAbility(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	comboQueue = CreateDefaultSubobject<UHIComboQueue>("comboQueue");
	comboQueue->HISetMaxWeight(MAX_WEIGHT);
	comboQueue->HISetQueueResetCooldown(QUEUE_RESET_COOLDOWN);
}


// Called when the game starts
void UHIComboManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	launchedComboAbility = NewObject<UHIComboAbility>();

	comboQueue->HIEmpty();
}

// Called every frame
void UHIComboManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (abilitySystem) 
	{
		if (!launchingAbility) 
		{
			//launchedComboAbility = NewObject<UHIComboAbility>();

			if (comboQueue->HIDequeue(launchedComboAbility)) 
			{
				abilitySystem->CallServerTryActivateAbility(launchedComboAbility->HIGetGameplayAbilityHandle(), false, FPredictionKey());
				abilitySystem->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(COMBO_TAG));
			}

			comboQueue->HIUpdate(DeltaTime);
		}
	}
}

void UHIComboManagerComponent::HIAttachAbilitySystem(UAbilitySystemComponent* attachedAbilitySystem)
{
	abilitySystem = attachedAbilitySystem;

	abilitySystem->AbilityActivatedCallbacks.AddUFunction(this, FName("HIOnComboAbilityActivated"));
	abilitySystem->AbilityEndedCallbacks.AddUFunction(this, FName("HIOnComboAbilityEnded"));
}

void UHIComboManagerComponent::HIAttachComboEvent(FEnqueueComboAbilityEvent& attachEvent, ComboAbilityAttachMode attachMode)
{

	switch (attachMode)
	{
	case ComboAbilityAttachMode::ENQUEUE:
		attachEvent.AddDynamic(this, &UHIComboManagerComponent::HIEnqueueAbility);
		break;
	case ComboAbilityAttachMode::RESET_ENQUEUE:
		attachEvent.AddDynamic(this, &UHIComboManagerComponent::HIResetComboAndEnqueueAbility);
		break;
	case ComboAbilityAttachMode::RESET_LAUNCH:
		attachEvent.AddDynamic(this, &UHIComboManagerComponent::HIResetComboAndLaunchAbility);
		break;
	}
}

void UHIComboManagerComponent::HIEnqueueAbility(TArray<UHIComboAbility*> comboAbility)
{
	if (CanEnqueueAbility())
	{
		if (comboQueue->HIEnqueue(comboAbility))
		{
			HIAddComboTag();
		}
	}
}

void UHIComboManagerComponent::HIResetComboAndEnqueueAbility(TArray<UHIComboAbility*> comboAbility)
{
	if (CanEnqueueAbility())
	{
		comboQueue->HIEmpty();
		if (comboQueue->HIEnqueue(comboAbility))
		{
			HIAddComboTag();
		}

	}
}

void UHIComboManagerComponent::HIResetComboAndLaunchAbility(TArray<UHIComboAbility*> comboAbility)
{
	if (CanEnqueueAbility())
	{
		if (launchedComboAbility)
		{
			if (comboAbility[0]->HIGetAbilityPriority() >= launchedComboAbility->HIGetAbilityPriority())
			{
				comboQueue->HIEmpty();
				abilitySystem->CallServerTryActivateAbility(comboAbility[0]->HIGetGameplayAbilityHandle(), false, FPredictionKey());
			}
		}
		else
		{
			comboQueue->HIEmpty();
			abilitySystem->CallServerTryActivateAbility(comboAbility[0]->HIGetGameplayAbilityHandle(), false, FPredictionKey());
		}

	}
}

void UHIComboManagerComponent::HIAddComboTag()
{
	if (launchingAbility)
	{
		abilitySystem->AddLooseGameplayTag(GET_GAMEPLAY_TAG(COMBO_TAG));
	}
}

void UHIComboManagerComponent::HIOnComboAbilityActivated(UGameplayAbility* launchedAbility)
{
	if (launchedAbility->AbilityTags.HasTag(GET_GAMEPLAY_TAG(COMBO_ABILITY_TAG)))
	{
		launchingAbility = true;
	}
}

void UHIComboManagerComponent::HIOnComboAbilityEnded(UGameplayAbility* launchedAbility)
{
	launchingAbility = false;
	//launchedComboAbility->ConditionalBeginDestroy();
	//launchedComboAbility = nullptr;
}

void UHIComboManagerComponent::HISetComboQueueWeight(int& comboQueueWeight)
{
	comboQueue->HISetMaxWeight(comboQueueWeight);
}

void UHIComboManagerComponent::HISetResetQueueCooldown(float& resetQueueCooldown)
{
	comboQueue->HISetQueueResetCooldown(resetQueueCooldown);
}

const bool UHIComboManagerComponent::CanEnqueueAbility() const
{
	FGameplayTagContainer abilitySystemTags;
	abilitySystem->GetOwnedGameplayTags(abilitySystemTags);
	if (abilitySystemTags.HasTag(GET_GAMEPLAY_TAG(CANCEL_ENQUEUE_TAG)))
	{
		return false;
	}

	return true;
}

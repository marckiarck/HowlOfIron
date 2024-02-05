// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Rage/HIChargedHeap.h"
#include <GAS/GameplayEffects/HIChargedValueGameplayEffect.h>
#include "HIMacros.h"

UHIChargedHeap::UHIChargedHeap() : currentChargeNode(nullptr), overloaded(false)
{
}

UHIChargedHeap::~UHIChargedHeap()
{
	
}

void UHIChargedHeap::HIInitialize(UHIChargeHeapDataAsset* chargeHeapDataAsset)
{
	HIEmpty();

	if (chargeHeapDataAsset)
	{
		currentChargeNode = NewObject<UHIChargeNode>();
		UHIChargeNode* previousCreatedChargeNode = nullptr;
		for (int i = 0; i < chargeHeapDataAsset->chargeNodeConfigurations.Num(); ++i)
		{
			//DataAsset are iterated from up to down
			FChargeNodeConfiguration chargeNodeConfiguration = chargeHeapDataAsset->chargeNodeConfigurations[i];
			UHIChargeNode* chargeNode = NewObject<UHIChargeNode>();
			if (i == 0)
			{
				chargeNode->HIInitializeChargeNode(chargeNodeConfiguration.chargeNodeFillValue, chargeNodeConfiguration.safeWeightCapacity, previousCreatedChargeNode, chargeNodeConfiguration.effectsApplied, chargeNodeConfiguration.removeEffectTag);
				currentChargeNode->HIInitializeChargeNode(chargeNodeConfiguration.chargeNodeFillValue, chargeNodeConfiguration.safeWeightCapacity, previousCreatedChargeNode, chargeNodeConfiguration.effectsApplied, chargeNodeConfiguration.removeEffectTag);
				previousCreatedChargeNode = currentChargeNode;
			}
			else
			{
				chargeNode->HIInitializeChargeNode(chargeNodeConfiguration.chargeNodeFillValue, chargeNodeConfiguration.safeWeightCapacity, previousCreatedChargeNode, chargeNodeConfiguration.effectsApplied, chargeNodeConfiguration.removeEffectTag);
				previousCreatedChargeNode = chargeNode;
			}

		}

		chargeAttributeeUpdateGameplayEffect = chargeHeapDataAsset->updateChargeValueGameplayEffect;

		HICalculateMaxChargedValueWeight(chargeHeapDataAsset);

		overloadDuration = chargeHeapDataAsset->overloadDuration;

		ensure(chargeAttributeeUpdateGameplayEffect);
		chargeAttributeeUpdateGameplayEffectRef = Cast<UGameplayEffect>(chargeAttributeeUpdateGameplayEffect->GetDefaultObject());
	}
	
}

void UHIChargedHeap::HIAttachAbilitySystem(UAbilitySystemComponent* abilitySystem)
{
	attachedAbilitySytem = abilitySystem;

	UHIChargeNode* referenceNode = currentChargeNode;
	while (referenceNode != nullptr)
	{
		referenceNode->HISetAbilitySystem(abilitySystem);
		referenceNode = referenceNode->HIGetNextChargeNode();
	}

	referenceNode = currentChargeNode->HIGetPreviousChargeNode();
	while (referenceNode != nullptr)
	{
		referenceNode->HISetAbilitySystem(abilitySystem);
		referenceNode = referenceNode->HIGetPreviousChargeNode();
	}

	attachedAbilitySytem->OnGameplayEffectAppliedDelegateToSelf.AddUFunction(this, FName("HIUpdateChargedHeapOnGameplayEffectAppliedToSelf"));
}

void UHIChargedHeap::HITryUpgradeChargeNode(unsigned int weightAdded)
{
	if (overloaded == false)
	{
		HIUpdatecurrentChargeWeightBasedOnAttributte();

		int extraWeight = HIAddChargeWeight(weightAdded);

		if (extraWeight > 0)
		{

			UHIChargeNode* nextChargeNode = currentChargeNode->HIChargeNextNode();
			if (nextChargeNode)
			{
				currentChargeNode = nextChargeNode;
				currentChargeWeight = 0;

				HIUpdateAttributeBasedOnCurrentChargeWeight(HICalculateTotalChargeWeight());
				HITryUpgradeChargeNode(extraWeight);
				return;
			}
			else {
				currentChargeWeight = currentChargeNode->HIGetChargeNodeFillValue();
				HIUpdateAttributeBasedOnCurrentChargeWeight(HICalculateTotalChargeWeight());
				HIOverloadChargeHeap();
			}

		}

		HIUpdateAttributeBasedOnCurrentChargeWeight(HICalculateTotalChargeWeight());
	}
	
}

void UHIChargedHeap::HITryDowngradeChargeNode(unsigned int weightRemoved)
{

	if (overloaded == false)
	{
		HIUpdatecurrentChargeWeightBasedOnAttributte();

		int extraWeight = HIRemoveChargeWeight(weightRemoved);
		if (extraWeight > 0)
		{

			UHIChargeNode* previousChargeNode = currentChargeNode->HIChargePreviousNode();
			if (previousChargeNode)
			{
				currentChargeNode = previousChargeNode;
				currentChargeWeight = currentChargeNode->HIGetChargeNodeFillValue();

				HIUpdateAttributeBasedOnCurrentChargeWeight(HICalculateTotalChargeWeight());
				HITryDowngradeChargeNode(extraWeight);
				return;
			}

		}

		HIUpdateAttributeBasedOnCurrentChargeWeight(HICalculateTotalChargeWeight());
	}
	
}

void UHIChargedHeap::HIOverloadChargeHeap()
{
	overloaded = true;
	HIUpdateAttributeBasedOnCurrentChargeWeight(HICalculateTotalChargeWeight());

	//Charged heap may not have world
	UHIGameData::HIGetPlayerWerewolf()->GetWorld()->GetTimerManager().SetTimer(OverloadTimerHandle, this, &UHIChargedHeap::HIReset, overloadDuration, false, overloadDuration);
	OnOverload.Broadcast();
}

void UHIChargedHeap::HICalculateMaxChargedValueWeight(UHIChargeHeapDataAsset* chargeHeapDataAsset)
{
	maxChargedValueWeight = 0.f;

	for (FChargeNodeConfiguration nodeConfiguration : chargeHeapDataAsset->chargeNodeConfigurations)
	{
		maxChargedValueWeight += nodeConfiguration.chargeNodeFillValue;
	}
}

void UHIChargedHeap::HIReset()
{
	overloaded = false;

	if (currentChargeNode)
	{
		HITryDowngradeChargeNode(HICalculateTotalChargeWeight());
	}
}

void UHIChargedHeap::HIEmpty()
{
	/*UHIChargeNode* referenceNode = currentChargeNode;
	if (referenceNode)
	{
		TArray<UHIChargeNode*> deletedNodes;
		while (referenceNode != nullptr)
		{
			deletedNodes.Add(referenceNode);
			referenceNode = referenceNode->HIGetNextChargeNode();
		}

		referenceNode = currentChargeNode->HIGetPreviousChargeNode();
		while (referenceNode != nullptr)
		{
			deletedNodes.Add(referenceNode);
			referenceNode = referenceNode->HIGetPreviousChargeNode();
		}

		for (UHIChargeNode* deletedNode : deletedNodes)
		{
			delete deletedNode;
		}
	}*/

	HIReset();
	currentChargeNode = nullptr;
	currentChargeWeight = 0;
}

int UHIChargedHeap::HIAddChargeWeight(unsigned int weightAdded)
{
	currentChargeNode->HIAddChargeSafeWeight(99999);
	currentChargeWeight += weightAdded;
	//currentChargeWeight += currentChargeNode->HIAddChargeSafeWeight(weightAdded);

	int chargeNodeFillValue = currentChargeNode->HIGetChargeNodeFillValue();
	if (currentChargeWeight > chargeNodeFillValue)
	{
		int returnedWeight = currentChargeWeight - chargeNodeFillValue;
		currentChargeWeight = chargeNodeFillValue;
		return returnedWeight;
	}
	else {
		return 0;
	}
}

int UHIChargedHeap::HIRemoveChargeWeight(unsigned int wightRemoved)
{
	currentChargeWeight -= currentChargeNode->HIRemoveChargeSafeWeight(wightRemoved);
	HIUpdateAttributeBasedOnCurrentChargeWeight(HICalculateTotalChargeWeight());

	if (currentChargeWeight < 0) 
	{
		int returnedWeight = -currentChargeWeight;
		currentChargeWeight = 0;
		return returnedWeight;
	}
	else {
		return 0;
	}
}

float UHIChargedHeap::HICalculateTotalChargeWeight()
{
	float totalChargeWeight = currentChargeWeight;

	if (currentChargeNode)
	{
		UHIChargeNode* chargeNodeIt = currentChargeNode->HIGetPreviousChargeNode();

		while (chargeNodeIt != nullptr)
		{
			totalChargeWeight += chargeNodeIt->HIGetChargeNodeFillValue();
			chargeNodeIt = chargeNodeIt->HIGetPreviousChargeNode();
		}
	}

	return totalChargeWeight;
}

float UHIChargedHeap::HIGetChargedAttributeValue()
{
	if (attachedAbilitySytem)
	{
		TArray<FGameplayAttribute> actorAttributes;
		attachedAbilitySytem->GetAllAttributes(actorAttributes);
		int index;
		actorAttributes.Find(UHICharacterAttributes::GetchargedValueAttribute(), index);

		return attachedAbilitySytem->GetNumericAttribute(actorAttributes[index]);
	}
	
	return 0.f;
}

void UHIChargedHeap::HIUpdatecurrentChargeWeightBasedOnAttributte()
{
	float chargedAttributeValue = HIGetChargedAttributeValue();
	float totalChargeWeight = HICalculateTotalChargeWeight();
	float valueDiference = totalChargeWeight - chargedAttributeValue;

	if (valueDiference != 0.f)
	{
		//You have to override the charged value attribute to avoid infinite loops
		HIUpdateAttributeBasedOnCurrentChargeWeight(totalChargeWeight);

		if (valueDiference > 0.f)
		{
			HITryDowngradeChargeNode(valueDiference);
		}
		else {
			HITryUpgradeChargeNode(-valueDiference);
		}		
	}
	
}

void UHIChargedHeap::HIUpdateAttributeBasedOnCurrentChargeWeight(float expectedAttribute)
{
	FGameplayEffectContextHandle effectContextHandle;
	FGameplayEffectSpec effectSpec = FGameplayEffectSpec(chargeAttributeeUpdateGameplayEffectRef, effectContextHandle);
	effectSpec.SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName(CHARGED_ATTRIBUTE_TAGS)), expectedAttribute);
	attachedAbilitySytem->ApplyGameplayEffectSpecToSelf(effectSpec);
}

void UHIChargedHeap::HIUpdateChargedHeapOnGameplayEffectAppliedToSelf(UAbilitySystemComponent* affectedAbilitySytem, const FGameplayEffectSpec& gameplayEffectSpec, FActiveGameplayEffectHandle gameplayEffectHandle)
{
	HIUpdatecurrentChargeWeightBasedOnAttributte();
}

int UHIChargedHeap::HIGetCurrentChargedValue()
{
	return int(HICalculateTotalChargeWeight());
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Rage/HIChargeNode.h"
#include <GAS/GameplayEffects/HIChargedValueGameplayEffect.h>

UHIChargeNode::UHIChargeNode() : chargeNodeFillValue(0), safeWeight(0), nextChargeNode(nullptr), previousChargeNode(nullptr), effectsAplied(false)
{
	gameplayEffectsToBeApplied.Empty();
}

void UHIChargeNode::HIInitializeChargeNode(int assigendChargeNodeFillValue, int assigendSafeWeightCapacity, UHIChargeNode* assignedPreviousChargeNode, TArray<TSubclassOf<UGameplayEffect>>& assignedEffectsApplied, FGameplayTag assignedTag)
{
	this->chargeNodeFillValue = assigendChargeNodeFillValue;
	this->safeWeightCapacity = assigendSafeWeightCapacity;
	this->previousChargeNode = assignedPreviousChargeNode;
	this->removeEffectsTag = assignedTag;

	if (assignedPreviousChargeNode)
	{
		assignedPreviousChargeNode->nextChargeNode = this;
	}	

	this->gameplayEffectsToBeApplied = assignedEffectsApplied;

	safeWeight = 0;
}

int UHIChargeNode::HIAddChargeSafeWeight(unsigned int weightAdded)
{
	safeWeight += int(weightAdded); //Be careful operating int with unsigned int

	if (safeWeight > safeWeightCapacity) {

		int returnedWeight = safeWeight - safeWeightCapacity;
		safeWeight = safeWeightCapacity;

		return returnedWeight;
	}
	else {
		return 0;
	}
}

int UHIChargeNode::HIRemoveChargeSafeWeight(unsigned int weightRemoved)
{
	safeWeight -= int(weightRemoved); //Be careful operating int with unsigned int
	if (safeWeight < 0) {

		int returnedWeight = -safeWeight;
		safeWeight = 0;

		return returnedWeight;
	}
	else {
		return 0;
	}
}

void UHIChargeNode::HIResetSafeWeight()
{
	safeWeight = 0;
}

UHIChargeNode* UHIChargeNode::HIChargeNextNode()
{

	HIApplyEffects();

	if (nextChargeNode)
	{
		nextChargeNode->safeWeight = nextChargeNode->safeWeightCapacity;
		return nextChargeNode;
	}
	else {
		return nullptr;
	}
	
}

UHIChargeNode* UHIChargeNode::HIChargePreviousNode()
{
	HIRemoveEffects();
	safeWeight = 0;

	if (previousChargeNode)
	{
		previousChargeNode->safeWeight = previousChargeNode->safeWeightCapacity;
		return previousChargeNode;
	}
	else {
		return nullptr;
	}
	
}

const int UHIChargeNode::HIGetChargeNodeFillValue() const
{
	return chargeNodeFillValue;
}

UHIChargeNode* const UHIChargeNode::HIGetNextChargeNode() const
{
	return nextChargeNode;
}

UHIChargeNode* const UHIChargeNode::HIGetPreviousChargeNode() const
{
	return previousChargeNode;
}

void UHIChargeNode::HISetAbilitySystem(UAbilitySystemComponent* newAbilitySytem)
{
	abilitySytem = newAbilitySytem;
}

void UHIChargeNode::HIApplyEffects()
{
	if (effectsAplied == false)
	{
		for (int i = 0; i < gameplayEffectsToBeApplied.Num(); ++i)
		{
			UGameplayEffect* effect = Cast<UGameplayEffect>(gameplayEffectsToBeApplied[i]->GetDefaultObject());

			FActiveGameplayEffectHandle effectHandle = abilitySytem->ApplyGameplayEffectToSelf(effect, 0.f, FGameplayEffectContextHandle());

			effect->ConditionalBeginDestroy();
		}

		effectsAplied = true;
	}
}

void UHIChargeNode::HIRemoveEffects()
{
	if (effectsAplied)
	{
		abilitySytem->RemoveActiveEffectsWithTags(FGameplayTagContainer(removeEffectsTag));
		effectsAplied = false;
	}
	
}

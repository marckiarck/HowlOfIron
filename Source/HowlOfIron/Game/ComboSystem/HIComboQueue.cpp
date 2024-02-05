// Fill out your copyright notice in the Description page of Project Settings.


#include "HIComboQueue.h"

UHIComboQueue::UHIComboQueue() : index(0)
{

}

void UHIComboQueue::HIUpdate(float deltaTime)
{
	timeFilled += deltaTime;

	if (timeFilled >= queueResetCooldown) {
		HIEmpty();
		timeFilled = 0.f;
	}

}

bool UHIComboQueue::HIDequeue(UHIComboAbility* ability_)
{
	if (abilitiesArray.Num() > 0) {
		ability_->HISetGameplayAbilityHandle(abilitiesArray[0]->HIGetGameplayAbilityHandle());
		ability_->HISetAbilityActivationDelay(abilitiesArray[0]->HIGetAbilityActivationDelay());
		ability_->HISetAbilityPriority(abilitiesArray[0]->HIGetAbilityPriority());
		ability_->HISetAbilityWeight(abilitiesArray[0]->HIGetAbilityWeight());
		abilitiesArray.RemoveAt(0);

		return true;
	}

	return false;
}

bool UHIComboQueue::HIEnqueue(TArray<UHIComboAbility*> _ability)
{
	int abilityIndex = maxWeight - freeWeight;
	abilityIndex = FMath::Max(0, abilityIndex);
	abilityIndex = FMath::Min(abilityIndex, maxWeight - 1);

	if (HIIsFull() == false) {
		UHIComboAbility* enqueuedAbility = _ability[abilityIndex];
		abilitiesArray.Add(enqueuedAbility);
		freeWeight -= enqueuedAbility->HIGetAbilityWeight();
		timeFilled = 0.f;

		return true;
	}
	else {

		//If queue is full the last element can be override by a ability with higher priority
		UHIComboAbility* enqueuedAbility = _ability[abilityIndex];
		if (abilitiesArray.Num() > 0 && enqueuedAbility->HIGetAbilityPriority() >= abilitiesArray[abilitiesArray.Num() - 1]->HIGetAbilityPriority()) {
			abilitiesArray[abilitiesArray.Num() - 1] = enqueuedAbility;
			return false;
		}

	}

	return false;
}

void UHIComboQueue::HIEmpty()
{
	abilitiesArray.Empty();

	freeWeight = maxWeight;

	index = 0;
}

bool UHIComboQueue::HIIsEmpty()
{
	return freeWeight == maxWeight;
}

bool UHIComboQueue::HIIsFull()
{
	return freeWeight <= 0;
}

const int UHIComboQueue::HIGetMaxWeight() const
{
	return maxWeight;
}

const int UHIComboQueue::HIGetQueueResetCooldown() const
{
	return queueResetCooldown;
}

void UHIComboQueue::HISetMaxWeight(int newMaxWeight)
{
	maxWeight = newMaxWeight;
}

void UHIComboQueue::HISetQueueResetCooldown(float newQueueResetCooldown)
{
	queueResetCooldown = newQueueResetCooldown;
}
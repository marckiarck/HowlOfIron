#include "HIComboAbility.h"

UHIComboAbility::UHIComboAbility()
{
}

const FGameplayAbilitySpecHandle UHIComboAbility::HIGetGameplayAbilityHandle() const
{
	return gameplayAbilityHandle;
}

const int UHIComboAbility::HIGetAbilityWeight() const
{
	return abilityWeight;
}

const int UHIComboAbility::HIGetAbilityPriority() const
{
	return abilityPriority;
}

const float UHIComboAbility::HIGetAbilityActivationDelay() const
{
	return abilityActivationDelay;
}

void UHIComboAbility::HISetGameplayAbilityHandle(const FGameplayAbilitySpecHandle& newGameplayAbility)
{
	gameplayAbilityHandle = newGameplayAbility;
}

void UHIComboAbility::HISetAbilityWeight(int newAbilityWeight)
{
	abilityWeight = newAbilityWeight;
}

void UHIComboAbility::HISetAbilityPriority(int newAbilityPriority)
{
	abilityPriority = newAbilityPriority;
}

void UHIComboAbility::HISetAbilityActivationDelay(float newAbilityActivationDelay)
{
	abilityActivationDelay = newAbilityActivationDelay;
}
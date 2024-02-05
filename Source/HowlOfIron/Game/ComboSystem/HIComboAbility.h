//Created by Marcos

#pragma once

#include "CoreMinimal.h"
#include <GameplayAbilitySpec.h>
#include "HIComboAbility.generated.h"


UCLASS()
/// <summary>
/// Class used to store elements in UHIComboQueue.
/// This class is a container of the properties of a GameeplayAbility.
/// </summary>
class UHIComboAbility : public UObject
{
	GENERATED_BODY()

public:
	UHIComboAbility();

private:

	/// <summary>
	/// Handle of a GameplayAbility. 
	/// This is the object that UAbilitySystemComponent is going to need to throw the GameplayAbility
	/// </summary>
	FGameplayAbilitySpecHandle gameplayAbilityHandle;

	/// <summary>
	/// Weight that is going to spend the ability in the UHIComboQueue to get enqueued
	/// </summary>
	int abilityWeight;

	/// <summary>
	/// Priority of the ability.
	/// If the priority of a ability is bigger or equal than other, that ability can take away that ability of the UHIComboQueue
	/// </summary>
	int abilityPriority;

	/// <summary>
	/// Time passed before the ability is launched
	/// </summary>
	/// <disclaimer> This attribute is not used in UHIComboQueue for now </disclaimer>
	float abilityActivationDelay;

public:
#pragma region GETTERS

	const FGameplayAbilitySpecHandle HIGetGameplayAbilityHandle() const;

	const int HIGetAbilityWeight() const;

	const int HIGetAbilityPriority() const;

	const float HIGetAbilityActivationDelay() const;

#pragma endregion

#pragma region SETTERS
	void HISetGameplayAbilityHandle(const FGameplayAbilitySpecHandle& newGameplayAbility);

	void HISetAbilityWeight(int newAbilityWeight);

	void HISetAbilityPriority(int newAbilityPriority);

	void HISetAbilityActivationDelay(float newAbilityActivationDelay);
#pragma endregion
};

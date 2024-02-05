//Created by Marcos

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HIComboAbility.h"
#include "HIComboQueue.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class HOWLOFIRON_API UHIComboQueue : public UObject
{
	GENERATED_BODY()

public:
	UHIComboQueue();

private:

	TArray<UHIComboAbility*> abilitiesArray;

	/// <summary>
	/// Variable that stores free weight. While this value is higher than 0 Abilities can be enqueued
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Queue | Weight")
		int freeWeight;

	/// <summary>
	/// Variable that stores the maximum freeWeigth the queue is going to have
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Queue | Weight")
		int maxWeight;

	/// <summary>
	/// Time that is going to elapse until queue will empty
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Queue | Time")
		float queueResetCooldown;

	/// <summary>
	/// Time elapsed since the queue has enqueued first ability
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Queue | Time")
		float timeFilled;

	/// <summary>
	/// Timer that calls Update in loop
	/// </summary>
	FTimerHandle updateTimer;

	/// <summary>
	/// Index of the next enqueued combo ability 
	/// </summary>
	int index;

public:

	/// <summary>
	/// Updates the time variables
	/// </summary>
	/// <param name="deltaTime"> time considered to update time variables </param>
	void HIUpdate(float deltaTime);

	/// <summary>
	/// Removes and returns the first ability of the queue.
	/// </summary>
	/// <param name="ability"> variable where first ability is going to be copied </param>
	/// <returns> true if the value was successfully copied, else return false </returns>
	bool HIDequeue(UHIComboAbility* ability_);

	/// <summary>
	/// Adds an ability to the end of the queue
	/// </summary>
	/// <param name="_ability"> Ability that is going to be added </param>
	/// <returns> true if ability was successfully added, else returns false </returns>
	/// <exception>
	/// when enqueue is full and an ability overrides the last ability it returns false
	/// </exception>
	bool HIEnqueue(TArray<UHIComboAbility*> _ability);

	/// <summary>
	/// Clears queue content
	/// </summary>
	void HIEmpty();

	/// <summary>
	/// Checks if the queue is empty
	/// </summary>
	/// <returns> true if the queue is empty, false if is not </returns>
	bool HIIsEmpty();

	/// <summary>
	/// Checks if queue is at maximum capacity. Queue is full when there is no freeWeight
	/// </summary>
	/// <returns> returns true if queue is full, else return false </returns>
	bool HIIsFull();

#pragma region GETTERS
	UFUNCTION()
		const int HIGetMaxWeight() const;

	UFUNCTION()
		const int HIGetQueueResetCooldown() const;
#pragma  endregion

#pragma region SETTERS
	UFUNCTION()
		void HISetMaxWeight(int newMaxWeight);

	UFUNCTION()
		void HISetQueueResetCooldown(float newQueueResetCooldown);
#pragma endregion
};

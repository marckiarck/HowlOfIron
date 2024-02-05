// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/HICharacterAttributes.h"
#include "Components/ActorComponent.h"
#include "HIDetectionConfiguration.h"
#include "HIDetectionDataAsset.h"
#include "HIDetectorActorComponent.generated.h"

UCLASS()
class HOWLOFIRON_API UHIDetectionAttributes : public UAttributeSet
{

	GENERATED_BODY()

public:
	UHIDetectionAttributes() {};


public:
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
		FGameplayAttributeData detectionValue;

public:
	ATTRIBUTE_ACCESSORS(UHIDetectionAttributes, detectionValue);
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HOWLOFIRON_API UHIDetectorActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHIDetectorActorComponent();


private:
	UPROPERTY(VisibleAnywhere)
		float detectionValue;

	UPROPERTY(VisibleAnywhere, meta = (displayName = "Detection lost per second"))
		float detectionLostValue;

	UPROPERTY(VisibleAnywhere)
		AActor* detectedActor;

	UPROPERTY(Transient, BlueprintType)
		UAbilitySystemComponent* attachedAbilitySystem;

	UPROPERTY(Transient)
		UHIDetectionConfiguration* detectionConfiguration;

	UPROPERTY(Transient)
		const UHIDetectionAttributes* detectionAttributes;

	UPROPERTY(EditAnywhere)
		UHIDetectionDataAsset* initialDetectionConfiguration;

	UPROPERTY(Transient)
		UGameplayEffect* gameplayeffect = nullptr;

	UPROPERTY()
		bool canDecrease;

	UPROPERTY()
	float decreaseWaitTimer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void HIUpdatedDetector(float DeltaTime);
	void HIAttachAbilitySystem(UAbilitySystemComponent* newAttachedAbilitySystem);
	void HIInitializeDetectionValue(UDataTable* abilityDataTable);
	void HISetDetectionConfiguration(UHIDetectionConfiguration* newDetectionConfiguration);
	void HISetDetectionConfiguration(UHIDetectionDataAsset* newDetectionAsset);
	void HISetDetectionLostValue(float newDetectionLostValue);
	const UHIDetectionAttributes* HIGetDetectionAttributes() const { return detectionAttributes; };
	void HISetInitialDetection() { HISetDetectionConfiguration(initialDetectionConfiguration); };
	void HISetDetectionValue(float _newValue);

	AActor* HIGetDetectedActor();

};

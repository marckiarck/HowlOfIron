// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Game/Conditions/HIBossLifeCondition.h>
#include <GameplayEffect.h>
#include "HILifeConditionComponent.generated.h"


UCLASS(editinlinenew, DefaultToInstanced, BlueprintType, Blueprintable)
class HOWLOFIRON_API UHIBossLifeContext : public UObject
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		UHIBossLifeCondition* lifeCondition;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> gameplayEffectClass;

	UPROPERTY()
		UGameplayEffect* appliedGameplayEffect;

	UPROPERTY()
		bool conditionMet = false;

public:
	void HICheckLifeCondition(class UAbilitySystemComponent* abilitySystem);
	void HIInitializeContext();
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOWLOFIRON_API UHILifeConditionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHILifeConditionComponent();

private:
	UPROPERTY(EditAnywhere, Instanced, Category = "Boss")
	TArray<UHIBossLifeContext*> lifeConditions;

	UPROPERTY(Transient)
		class UAbilitySystemComponent* ownerAbilitySystem;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

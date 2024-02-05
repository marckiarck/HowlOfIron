// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HIConditionRegister.generated.h"

UCLASS()
class UHIConditionConfiguration : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient)
		UHICondition* condition;

	UPROPERTY()
		bool meetOnce;
};

UCLASS()
class HOWLOFIRON_API AHIConditionRegister : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHIConditionRegister();

private:
	static UPROPERTY(Transient) AHIConditionRegister* instance;

	UPROPERTY(Transient)
	TArray<UHIConditionConfiguration*> registeredCoditions;

	/// <summary>
	/// Intermediate array used to add conditions safely to registerConditions array
	/// </summary>
	UPROPERTY(Transient)
	TArray<UHIConditionConfiguration*> newConditions;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		static AHIConditionRegister* HIGetConditionRegister();

	UFUNCTION()
	static void HIResetConditionRegister();

	UFUNCTION(BlueprintCallable)
	void HIRegisterCondition(UHICondition* registeredCondition, bool meetOnce, bool initializeCondition = false);
};

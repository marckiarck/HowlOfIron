// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Game/Weapons/HIGrenade.h"
#include "HISpawnGrenade.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGrenadeEndTaskLaunch, AHIGrenade*, spawnedGrenade);

UCLASS()
class HOWLOFIRON_API UHISpawnGrenade : public UAbilityTask
{
	GENERATED_BODY()

public:
	UHISpawnGrenade();

public:
	UPROPERTY(BlueprintAssignable)
		FOnGrenadeEndTaskLaunch onEndLaunch;

private:
	TSubclassOf<AHIGrenade> grenadeClass; 
	USkeletalMeshComponent* assignedOwnerSkeletalMesh; 
	FName assignedSocketName;
	FVector spawnLocation;
	FVector objetivePosition;

	AHIGrenade* spawnedGrenade;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHISpawnGrenade* HISpwanGrenade(UGameplayAbility* OwningAbility, TSubclassOf<AHIGrenade> grenadeType, FVector spawnPosition, FVector grenadeObjetive);

private:
	virtual void Activate() override;

	UFUNCTION()
	void OnGrenadeEndLaunch();

};

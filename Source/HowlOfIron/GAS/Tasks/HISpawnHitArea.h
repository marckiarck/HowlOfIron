// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HISpawnHitArea.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitAreaSpawnedDelegate, const AHIHitAreaActor*, spawnedHitArea);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitAreaDestroyDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitStopAimDelegate);

UCLASS()
class HOWLOFIRON_API UHISpawnHitArea : public UAbilityTask
{
	GENERATED_BODY()

public:
	UHISpawnHitArea();

private:
	TSubclassOf<AHIHitAreaActor> hitAreaClass;
	float lifeTime;
	float aimDuration;
	float rayLength;

	UPROPERTY(Transient)
	USceneComponent* emiterComponent;
	FName emiterSocketName;

	UPROPERTY(Transient)
	AActor* objetive;

	FVector attachOffset;

	FVector ShootHitPoint;


	AHIHitAreaActor* spawnedHitArea;

	UPROPERTY(BlueprintAssignable)
		FHitAreaSpawnedDelegate OnSpawned;

	UPROPERTY(BlueprintAssignable)
		FHitStopAimDelegate OnStopAim;

	UPROPERTY(BlueprintAssignable)
		FHitAreaDestroyDelegate OnHitAreaDestroy;

	float elapsedTime;

	bool onStopAimUsed;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHISpawnHitArea* HISpawnHitArea(UGameplayAbility* OwningAbility, TSubclassOf<AHIHitAreaActor> hitAreaActor, float areaHitLifeTime, float objetiveAimDuration, float areaHitRayLength, USceneComponent* componentAttachedTo, FName attachedToSocketName, FVector attachOffset = FVector(0.f), AActor* hitObjetive = nullptr, FVector HitPoint = FVector(0.f));

private:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
};

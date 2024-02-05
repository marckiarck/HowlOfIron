// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "HITagRemovedAndBoxCastBySock.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBoxHitBySocketDelegate, const FHitResult, HitResult,const FHitResult, FloorResult);

UCLASS()
class HOWLOFIRON_API UHITagRemovedAndBoxCastBySock : public UAbilityTask_WaitGameplayTagRemoved
{
	GENERATED_BODY()

public:
	UHITagRemovedAndBoxCastBySock();

private:
	FName socketName;

	USkeletalMeshComponent* ownerSkeletalMesh;

	FVector positionOffset;

	FVector boxSize;

	FVector boxCenter;

	UPROPERTY(Transient)
	AActor* hittedActor;

	bool tagRemoved;

	UPROPERTY(Transient)
	TArray<AActor*> hittedActors;

public:
	UPROPERTY(BlueprintAssignable)
		FBoxHitBySocketDelegate OnHit;

	UPROPERTY(BlueprintAssignable)
		FBoxHitBySocketDelegate OnDiferentActorHit;

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHITagRemovedAndBoxCastBySock* HITagRemovedAndBoxCastBySock(UGameplayAbility* OwningAbility, FVector boxSize, USkeletalMeshComponent* assignedOwnerSkeletalMesh, FName assignedSocketName, FVector assignedPositionOffset, FGameplayTag removedTag);

	virtual void TickTask(float DeltaTime) override;
	virtual void GameplayTagCallback(const FGameplayTag RemovedTag, int32 NewCount) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	void HIUpdateCenterPosition();
	void AddHittedActor(FHitResult& hitResult);
};

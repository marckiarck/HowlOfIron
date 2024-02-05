// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "HITagRemovedAndCapsuleCastBySock.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCapsuleHitBySocketDelegate, const FHitResult, HitResult, const FHitResult,FloorResult);

UCLASS()
class HOWLOFIRON_API UHITagRemovedAndCapsuleCastBySock : public UAbilityTask_WaitGameplayTagRemoved
{
	GENERATED_BODY()
	
public:
	UHITagRemovedAndCapsuleCastBySock();

private:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "SocketName"))
		FName socketName;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "SkeletalMeshOwnerOfSocket"))
		USkeletalMeshComponent* ownerSkeletalMesh;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "SocketPositionOffset"))
		FVector positionOffset;


	UPROPERTY(EditAnywhere, meta = (DisplayName = "SocketPositionOffset"))
		FRotator rotationOffset;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "CapsuleRadious"))
	float capsuleRadius;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "CapsuleHalfHeight"))
	float capsuleHalfHeight;

	FVector capsuleCenter;

	UPROPERTY(Transient)
	AActor* hittedActor;

	bool tagRemoved;

	UPROPERTY(Transient)
	TArray<AActor*> hittedActors;

public:
	UPROPERTY(BlueprintAssignable)
		FCapsuleHitBySocketDelegate OnHit;



public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHITagRemovedAndCapsuleCastBySock* HITagRemovedAndCapsuleCastBySock(UGameplayAbility* OwningAbility, float assigendCapsuleRadius, float assignedcapsuleHalfHeight, USkeletalMeshComponent* assignedOwnerSkeletalMesh, FName assignedSocketName, FVector assignedPositionOffset,FRotator _rotationOffset, FGameplayTag removedTag);

	virtual void TickTask(float DeltaTime) override;
	virtual void GameplayTagCallback(const FGameplayTag RemovedTag, int32 NewCount) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	void HIUpdateCenterPosition();
	void AddHittedActor(FHitResult& hitResult);
};

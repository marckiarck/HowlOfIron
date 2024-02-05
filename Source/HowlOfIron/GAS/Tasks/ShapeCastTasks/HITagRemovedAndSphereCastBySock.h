// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "HITagRemovedAndSphereCastBySock.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSphereHitBySocketDelegate, const FHitResult, HitResult,const FHitResult, FloorResult);

UCLASS()
class HOWLOFIRON_API UHITagRemovedAndSphereCastBySock : public UAbilityTask_WaitGameplayTagRemoved
{
	GENERATED_BODY()
	
public:
	UHITagRemovedAndSphereCastBySock();

private:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "SocketName"))
		FName socketName;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "SkeletalMeshOwnerOfSocket"))
		USkeletalMeshComponent* ownerSkeletalMesh;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "SocketPositionOffset"))
		FVector positionOffset;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "CapsuleRadious"))
		float sphereRadius;

	FVector sphereCenter;

	UPROPERTY(Transient)
	AActor* hittedActor;

	bool tagRemoved;

	UPROPERTY(Transient)
	TArray<AActor*> hittedActors;

public:
	UPROPERTY(BlueprintAssignable)
		FSphereHitBySocketDelegate OnHit;



public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHITagRemovedAndSphereCastBySock* HITagRemovedAndSphereCastBySock(UGameplayAbility* OwningAbility, float assignedSphereRadius, USkeletalMeshComponent* assignedOwnerSkeletalMesh, FName assignedSocketName, FVector assignedPositionOffset, FGameplayTag removedTag);

	virtual void TickTask(float DeltaTime) override;
	virtual void GameplayTagCallback(const FGameplayTag RemovedTag, int32 NewCount) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	void HIUpdateCenterPosition();
	void AddHittedActor(FHitResult& hitResult);
};

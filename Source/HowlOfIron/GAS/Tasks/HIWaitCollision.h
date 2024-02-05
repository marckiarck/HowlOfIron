// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HIWaitCollision.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOwnerHit, const FHitResult&, hitResult);

UCLASS()
class HOWLOFIRON_API UHIWaitCollision : public UAbilityTask
{
	GENERATED_BODY()

public:
	UHIWaitCollision();
	~UHIWaitCollision() {};

private:
	UPROPERTY(BlueprintAssignable)
	FOnOwnerHit OnOwnerHit;

	UPROPERTY(Transient)
	class UCapsuleComponent* capsuleComponent;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHIWaitCollision* HIWaitCollision(UGameplayAbility* OwningAbility);
	
private:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
};

// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "UObject/ObjectMacros.h"
#include "HITask_Jump.generated.h"

/**
 *
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivateJump);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndJump);

class ACharacter;
class USplineComponent;

UCLASS()
class HOWLOFIRON_API UHITask_Jump : public UAbilityTask
{
	GENERATED_BODY()


public:

	UHITask_Jump();

public:

	UPROPERTY(BlueprintAssignable)
		FActivateJump OnActive;

	UPROPERTY(BlueprintAssignable)
		FEndJump OnEnd;

protected:


private:
	ACharacter* owner;
	float jumpVelocity;
	TArray<FVector> splinePoints;

	FAlphaBlend jumpBlend;
	UPROPERTY(Transient)
		class USplineComponent* jumpSpline;

	bool werewolfCollisionEnabled = true;

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHITask_Jump* HIJump(UGameplayAbility* OwningAbility, float _velocity, TArray<FVector> _splinePoints);


protected:


private:

	virtual void Activate() override;

	virtual void TickTask(float DeltaTime) override;
};

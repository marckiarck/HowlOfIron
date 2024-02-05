// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Components/TimelineComponent.h"
#include "UObject/ObjectMacros.h"
#include "HITask_Climb.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivateClimb);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndClimb);

class ACharacter;
class USplineComponent;

UCLASS()
class HOWLOFIRON_API UHITask_Climb : public UAbilityTask
{
	GENERATED_BODY()
	
public:

	UHITask_Climb();

public:

	UPROPERTY(BlueprintAssignable)
		FActivateClimb OnActive;

	UPROPERTY(BlueprintAssignable)
		FEndClimb OnEnd;

protected:

private:

	ACharacter* owner;
	FAlphaBlend climbingBlend;
	
	float heightOfWall;
	float climbingSpeed;
	float distanceToClimb;
	float distanceToStartPoint;


	UPROPERTY(Transient)
		USplineComponent* climbSpline;

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHITask_Climb* HIClimb(UGameplayAbility* OwningAbility, float _climbingSpeed, float _heightOfWall);


protected:


private:

	virtual void Activate() override;

	virtual void TickTask(float DeltaTime) override;
};

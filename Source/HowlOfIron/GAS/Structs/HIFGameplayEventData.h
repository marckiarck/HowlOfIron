//Created by Marcos

#pragma once

#include "CoreMinimal.h"
#include <Abilities/GameplayAbilityTypes.h>
#include "HIFGameplayEventData.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UHIAbilityData : public UObject
{
    GENERATED_BODY()


public:
    UHIAbilityData(const FObjectInitializer& ObjectInitializer);



    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector VectorPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector jumpTargetPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float heightOfWallToClimb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector finisherPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool backExecution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName stringData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool wallClimb;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector wallPosition;

};


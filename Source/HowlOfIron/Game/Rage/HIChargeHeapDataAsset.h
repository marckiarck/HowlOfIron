//Created by Marcos

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <GameplayEffect.h>
#include "HIChargeHeapDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FChargeNodeConfiguration
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Fill value"))
		int chargeNodeFillValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Safe weight max capacity"))
		int safeWeightCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Effects applied"))
		TArray<TSubclassOf<UGameplayEffect>> effectsApplied;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Remove effects tag"))
		FGameplayTag removeEffectTag;

};

UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API UHIChargeHeapDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChargeHeap | Essentials", meta = (DisplayName = "Charge value change game effect"))
		TSubclassOf<UGameplayEffect> updateChargeValueGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChargeHeap", meta = (DisplayName = "Weight lost per tick"))
		int WeightLostPerTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChargeHeap", meta = (DisplayName = "Time passed beetwen wegith lost"))
		float weightLostColdown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChargeHeap", meta = (DisplayName = "Overload duration"))
		float overloadDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChargeHeap", meta = (DisplayName = "Charges"))
		TArray<FChargeNodeConfiguration> chargeNodeConfigurations;
};

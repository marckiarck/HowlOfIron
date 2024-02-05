#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FHIWerewolfSound.generated.h"



USTRUCT(BlueprintType)
struct HOWLOFIRON_API FHIWerewolfSound : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "radius"))
        float radius= 2000.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "force"))
        float force = 30.f;


    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "LossLowSteam"))
        //Value between 0 to 1
        float percentDiscountLowSteam = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "LossHighSteam"))
        //Value between 0 to 1
        float percentDiscountHighSteam = 1.f;


    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "MinumValue"))
  
        float minumvalue =0.f;


};

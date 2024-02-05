// @AUTHORS: Guillermo Suárez
#pragma once

#include "CoreMinimal.h"
#include "HIRowClass.h"
#include "HIRowClassSlider.generated.h"

class UHISliderClass;

UCLASS()
class HOWLOFIRON_API UHIRowClassSlider : public UHIRowClass
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHISliderClass* customSlider;

protected:


private:
        float sliderValue;

public:
    UFUNCTION(BlueprintCallable)
        void HISetValue(float _value);

    UFUNCTION(BlueprintCallable)
        float HIGetValue();

protected:


private:


};

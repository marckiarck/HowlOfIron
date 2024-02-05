// @AUTHOR: Guillermo Suárez, Germán López
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HISliderClass.generated.h"


UCLASS()
class HOWLOFIRON_API UHISliderClass : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class USlider* mainSlider;


protected:


private:
    float minVal;

    float maxVal;

public:

    UFUNCTION()
        void HISetMinValue(float _value);

    UFUNCTION()
        void HISetMaxValue(float _value);

    UFUNCTION()
        float HIGetMinValue();

    UFUNCTION()
        float HIGetMaxValue();

protected:


private:


};

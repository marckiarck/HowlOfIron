// @AUTHOR: Guillermo Suárez, Germán López


#include "HISliderClass.h"
#include "Components/Slider.h"

bool UHISliderClass::Initialize()
{
    Super::Initialize();


    return true;
}

void UHISliderClass::NativePreConstruct()
{
    Super::NativePreConstruct();

    minVal = mainSlider->MinValue;
    maxVal = mainSlider->MaxValue;
}

void UHISliderClass::NativeConstruct()
{
    Super::NativeConstruct();
}

void UHISliderClass::HISetMinValue(float _value)
{
    minVal = _value;
    mainSlider->SetMinValue(minVal);
}

void UHISliderClass::HISetMaxValue(float _value)
{
    maxVal = _value;
    mainSlider->SetMaxValue(maxVal);
}

float UHISliderClass::HIGetMinValue()
{
    return minVal;
}

float UHISliderClass::HIGetMaxValue()
{
    return maxVal;
}

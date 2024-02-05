// @AUTHORS: Guillermo Suárez


#include "HIRowClassSlider.h"
#include "UI/Utilities/HISliderClass.h"

bool UHIRowClassSlider::Initialize()
{
    Super::Initialize();



    return true;
}

void UHIRowClassSlider::NativePreConstruct()
{
    Super::NativePreConstruct();
    

}

void UHIRowClassSlider::NativeConstruct()
{
    Super::NativeConstruct();

    customSlider->HISetMinValue(customSlider->mainSlider->MinValue);
    customSlider->HISetMaxValue(customSlider->mainSlider->MaxValue);
    customSlider->mainSlider->SetValue(sliderValue);
}

void UHIRowClassSlider::HISetValue(float _value)
{
    sliderValue = _value;

    if (sliderValue < customSlider->HIGetMinValue())
    {
        sliderValue = customSlider->HIGetMinValue();
    }

    if (sliderValue > customSlider->HIGetMaxValue())
    {
        sliderValue = customSlider->HIGetMaxValue();
    }

    if (customSlider)
    {
        customSlider->mainSlider->SetValue(sliderValue);
    }
}

float UHIRowClassSlider::HIGetValue()
{
    return sliderValue;
}

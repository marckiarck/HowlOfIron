// @AUTHOR: Guillermo Suárez, Germán López

#include "HIRowClass.h"
#include "HITextSwitcher.h"
#include "HITextClass.h"
#include "Components/Image.h"


bool UHIRowClass::Initialize()
{
    Super::Initialize();



    if (overridenWidth < 500)
    {
        overridenWidth = 500;
    }

    return true;
}

void UHIRowClass::NativePreConstruct()
{
    Super::NativePreConstruct();

    settingText->HISetCustomText(useCustomText ? customText : FText::FromString(TEXT("Example Text")));

    rowContainer->bOverride_MinDesiredWidth = true;
    rowContainer->SetMinDesiredWidth(useOverridenWidth ? overridenWidth : 500);

    if (useCustomTextStyleData)
    {
        settingText->HISetCustomTextStyle(textStyleData);
    }

    if (selectedRowImage)
    {
        selectedRowImage->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UHIRowClass::NativeConstruct()
{
    Super::NativeConstruct();

}

void UHIRowClass::HIFocused_Implementation()
{
    if (selectedRowImage->GetVisibility() == ESlateVisibility::Collapsed)
    {
        selectedRowImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void UHIRowClass::HIClearFocus_Implementation()
{
    if (selectedRowImage->GetVisibility() == ESlateVisibility::Visible)
    {
        selectedRowImage->SetVisibility(ESlateVisibility::Collapsed);
    }
}

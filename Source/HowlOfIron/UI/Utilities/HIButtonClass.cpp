// @AUTHOR: Guillermo Su�rez, Germ�n L�pez


#include "HIButtonClass.h"
#include "HITextClass.h"
#include "Components/Button.h"


bool UHIButtonClass::Initialize()
{
    Super::Initialize();
    
    return true;
}

void UHIButtonClass::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (customButton)
    {
        customButton->SetBackgroundColor(FLinearColor::FromSRGBColor(FColor::White));
    }
    
    customButton->SetRenderOpacity(showButtonBackground ? 1 : 0);

    if (customTextButton)
    {
        customTextButton->HISetCustomText( useButtonText ? buttonText : FText::FromString(TEXT("Example Text")));
    }

    if (useCustomTextStyleData)
    {
        customTextButton->HISetCustomTextStyle(textStyleData);
    }
}

void UHIButtonClass::NativeConstruct()
{
    Super::NativeConstruct();
    
}

void UHIButtonClass::HIFocused()
{
    customButton->SetBackgroundColor(FLinearColor::FromSRGBColor(FColor::Silver));
}

void UHIButtonClass::HIClearFocus()
{
    customButton->SetBackgroundColor(FLinearColor::FromSRGBColor(FColor::White));
}
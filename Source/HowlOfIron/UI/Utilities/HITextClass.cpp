// @AUTHOR: Guillermo Suárez, Germán López


#include "HITextClass.h"
#include "Components/RichTextBlock.h"

bool UHITextClass::Initialize()
{
    Super::Initialize();


    return true;
}

void UHITextClass::NativePreConstruct()
{
    Super::NativePreConstruct();
    
    customRichText->SetText(useCustomText ? customText : FText::FromString(TEXT("Example Text")));

    if (useCustomTextStyleData)
    {
        HISetCustomTextStyle(textStyleData);
    }
}

void UHITextClass::NativeConstruct()
{
    Super::NativeConstruct();

}

void UHITextClass::HISetCustomText(FText newText)
{
    customText = newText;
    customRichText->SetText(customText);
}

void UHITextClass::HISetCustomTextStyle(UDataTable* newTextStyleData)
{
    customRichText->SetTextStyleSet(newTextStyleData);
}

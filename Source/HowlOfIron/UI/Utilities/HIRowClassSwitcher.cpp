// @AUTHOR: Guillermo Suárez, Germán López

#include "HIRowClassSwitcher.h"

bool UHIRowClassSwitcher::Initialize()
{
    Super::Initialize();



    return true;
}

void UHIRowClassSwitcher::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (useChoices)
    {
        settingSwitcher->HISetChoices(choices);
        settingSwitcher->HIUpdateIndex(settingSwitcher->index);
    }
    else
    {
        TArray<FText> exampleChoices;
        exampleChoices.Add(FText::FromString(TEXT("Choice 01")));
        exampleChoices.Add(FText::FromString(TEXT("Choice 02")));
        exampleChoices.Add(FText::FromString(TEXT("Choice 03")));
        settingSwitcher->HISetChoices(exampleChoices);
        settingSwitcher->HIUpdateIndex(0);
    }

    if (useSwitchTextStyleData)
    {
        settingSwitcher->customSwitcherText->HISetCustomTextStyle(switchTextStyleData);
    }
}

void UHIRowClassSwitcher::NativeConstruct()
{
    Super::NativeConstruct();


}

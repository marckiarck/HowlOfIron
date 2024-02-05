// @AUTHORS: Guillermo Suárez, Germán López


#include "HITextSwitcher.h"


bool UHITextSwitcher::Initialize()
{
    Super::Initialize();

    canChange = true;

    if (useChoices)
    {
        HISetChoices(choices);
        HIUpdateIndex(0);
    }
    else
    {
        TArray<FText> exampleChoices;
        exampleChoices.Add(FText::FromString(TEXT("Choice 01")));
        exampleChoices.Add(FText::FromString(TEXT("Choice 02")));
        exampleChoices.Add(FText::FromString(TEXT("Choice 03")));
        HISetChoices(exampleChoices);
        HIUpdateIndex(0);
        index = 0;
    }

    return false;
}

void UHITextSwitcher::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (useSwitchTextStyleData)
    {
        customSwitcherText->HISetCustomTextStyle(switchTextStyleData);
    }

}

void UHITextSwitcher::NativeConstruct()
{
    Super::NativeConstruct();

    UPanelWidget* rootWidget = Cast<UPanelWidget>(GetRootWidget());

    currentIndex = 0;
    HIUpdateIndex(index);
}

int UHITextSwitcher::HIUpdateIndex(int newIndex)
{
    if (newIndex >= choices.Num())
    {
        currentIndex = 0;
    }
    else if (newIndex < 0)
    {
        currentIndex = choices.Num() - 1;
    }
    else
    {
        currentIndex = newIndex;
    }

    if (choices.Num() != 0)
    {
        customSwitcherText->HISetCustomText(choices[currentIndex]);
    }

    index = currentIndex;
    return currentIndex;
}

void UHITextSwitcher::HISetChoices(TArray<FText> _choices)
{
    choices = _choices;
}


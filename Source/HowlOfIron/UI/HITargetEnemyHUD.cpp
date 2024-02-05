// @AUTHOR: Guillermo Suarez 
#include "UI/HITargetEnemyHUD.h"

void UHITargetEnemyHUD::NativePreConstruct()
{
    Super::NativePreConstruct();


}

void UHITargetEnemyHUD::NativeConstruct()
{
    Super::NativeConstruct();


}

bool UHITargetEnemyHUD::Initialize()
{
    Super::Initialize();

    return true;
}

void UHITargetEnemyHUD::HISetTargetImageVisibility(ESlateVisibility _visibility)
{
    if (targetImage)
    {
        targetImage->SetVisibility(_visibility);
    }
}
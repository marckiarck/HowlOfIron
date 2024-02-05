// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Tooltips/HITooltipWidget.h"

bool UHITooltipWidget::Initialize()
{
    Super::Initialize();

    tooltipData = NewObject<UHITooltipData>();

    return true;
}

void UHITooltipWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
}

void UHITooltipWidget::NativeConstruct()
{
    Super::NativeConstruct();

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Tooltips/HITooltipData.h"
#include <MediaAssets/Public/MediaSource.h>
#include <MediaAssets/Public/MediaPlayer.h>

void UHITooltipData::HICopyTooltipData(UHITooltipData* otherTooltip)
{
	this->tooltipTitle = otherTooltip->tooltipTitle;
	this->customTooltipTextStruct = otherTooltip->customTooltipTextStruct;
	this->sizeY = otherTooltip->sizeY;
	this->videoToPlay = otherTooltip->videoToPlay;
}

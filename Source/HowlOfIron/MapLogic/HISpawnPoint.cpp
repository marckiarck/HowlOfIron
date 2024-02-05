// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLogic/HISpawnPoint.h"
#include "MapLogic/HIComponentVisualizer.h"

AHISpawnPoint::AHISpawnPoint()
{
	componentVisualizer = CreateDefaultSubobject<UHIComponentVisualizer>(TEXT("ComponentVisualizer"));
}

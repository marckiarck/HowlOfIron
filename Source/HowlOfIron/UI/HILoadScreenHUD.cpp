// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HILoadScreenHUD.h"

void UHILoadScreenHUD::NativePreConstruct()
{

}

void UHILoadScreenHUD::NativeConstruct()
{

}

void UHILoadScreenHUD::LoadSceneAsync()
{
//	LoadPackageAsync();
}

void UHILoadScreenHUD::ChangeScene()
{
	if (timer > 2)
	{

	}
}

bool UHILoadScreenHUD::Initialize()
{
	Super::Initialize();

	LoadSceneAsync();

	return true;
}
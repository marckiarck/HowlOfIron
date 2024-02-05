// @AUTHOR: Carlos


#include "HIButtonHUD.h"
#include "HIButtonHUDWidget.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AHIButtonHUD::AHIButtonHUD()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = rootSceneComponent;

	buttonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ButtonWidget"));
	buttonWidget->SetupAttachment(rootSceneComponent);
	buttonWidget->SetVisibility(false);
	buttonVisible = false;

}

void AHIButtonHUD::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(-100000.f, -100000.f, -100000.f));
}

void AHIButtonHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	SetActorLocation(FMath::VInterpTo(GetActorLocation(), movePosition, DeltaTime, moveSpeed));
	
}

void AHIButtonHUD::Move(FVector _movePosition)
{
	movePosition = _movePosition;
}

void AHIButtonHUD::SetVisibility(bool visibility)
{
	buttonWidget->SetVisibility(visibility);

	if (buttonVisible != visibility)
	{
		buttonVisible = visibility;

		SetActorLocation(movePosition);
	}	
}


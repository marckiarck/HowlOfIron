// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HIButtonHUD.generated.h"

UCLASS()
class HOWLOFIRON_API AHIButtonHUD : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHIButtonHUD();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* rootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* buttonWidget;

private:
	UPROPERTY()
		FVector movePosition;

	UPROPERTY(EditAnywhere)
	float moveSpeed;

private:
	bool buttonVisible;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Move(FVector _movePosition);
	void SetVisibility(bool visibility);

};

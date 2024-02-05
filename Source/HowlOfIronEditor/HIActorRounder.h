// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HIActorRounder.generated.h"

UENUM(BlueprintType)
enum ERoundingType
{
	Round    = 0  UMETA(DisplayName = "Round"),
	Truncate = 1  UMETA(DisplayName = "Truncate")
};

UCLASS()
class HOWLOFIRONEDITOR_API AHIActorRounder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHIActorRounder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor Rounder", meta = (ToolTip = "Sets rounding type (Round or Truncate)."))
		TEnumAsByte<ERoundingType> type;

	UFUNCTION(CallInEditor, BlueprintImplementableEvent, Category = "Actor Rounder", meta = (Tooltip = "Updates actor location to a rounded/truncated one."))
		void RoundActorsLocation();

	UFUNCTION(CallInEditor, BlueprintImplementableEvent, Category = "Actor Rounder", meta = (Tooltip = "Updates actor rotation to a rounded/truncated one."))
		void RoundActorsRotation();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HICharacter.generated.h"

UCLASS()
class HOWLOFIRON_API AHICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHICharacter();

public:
    UPROPERTY(BlueprintReadWrite)
        bool isDead = false;


protected:

private:



public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable)
   const bool HIGetDebugMode() const ;


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:


};

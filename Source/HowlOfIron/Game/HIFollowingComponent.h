// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HIFollowingComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HOWLOFIRON_API UHIFollowingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHIFollowingComponent();



public:


    UPROPERTY(EditAnywhere)
    //The object you add this component will follow the first actor of the type you set down
    TSubclassOf<AActor> typeOfObjectToFollow;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector offset;




protected:

private:

UPROPERTY(Transient)
AActor* actorToFollow;


public:

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;


private:



};

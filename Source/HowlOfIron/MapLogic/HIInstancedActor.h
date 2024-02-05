// @AUTHORS: Marco Fernández, Guillermo Suárez
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "HIInstancedActor.generated.h"

UCLASS()
class HOWLOFIRON_API AHIInstancedActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AHIInstancedActor();

public:
    UPROPERTY(VisibleAnywhere)
        UInstancedStaticMeshComponent* instancedstaticMeshComponent = nullptr;

protected:

private:

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UInstancedStaticMeshComponent* HIGetInstancedMeshComponent();

    UFUNCTION(CallInEditor)
    void DesInstacianeitor();



protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:

};

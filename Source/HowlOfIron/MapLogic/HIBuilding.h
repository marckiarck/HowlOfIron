// @AUTHOR: Guille, Carlos

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/StaticMeshComponent.h>
#include "HIBuilding.generated.h"

// @TODO: Remove this class
UCLASS()
class HOWLOFIRON_API AHIBuilding : public AActor
{
	GENERATED_BODY()

public:
	AHIBuilding();
	~AHIBuilding() { UE_LOG(LogTemp, Log, TEXT("Building object deleted.")); }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
		USceneComponent* sceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
		USceneComponent* sceneComponentMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
		UStaticMeshComponent* staticMeshComponent;

protected:
	virtual void BeginPlay() override;

private:


public:

protected:


private:

};

// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HIAnchorage.generated.h"

UCLASS()
class HOWLOFIRON_API AHIAnchorage : public AActor
{
	GENERATED_BODY()
	
public:	
	AHIAnchorage();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anchorage")
		USceneComponent* sceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anchorage")
		class UBoxComponent* boxComponent;

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};

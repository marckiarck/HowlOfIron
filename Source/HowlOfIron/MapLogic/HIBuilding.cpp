// @AUTHOR: Guille, Carlos

#include "HIBuilding.h"
#include "HIMacros.h"

AHIBuilding::AHIBuilding()
{

	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(sceneComponent);

	sceneComponentMesh = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponentMesh"));
	sceneComponentMesh->SetupAttachment(sceneComponent);

	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	staticMeshComponent->SetupAttachment(sceneComponentMesh);
	staticMeshComponent->SetCollisionResponseToChannel(GAME_TRACE_BUILDING, ECollisionResponse::ECR_Block);

}

void AHIBuilding::BeginPlay()
{
	Super::BeginPlay();

}

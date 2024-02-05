// @AUTHOR: Carlos Fernandez

#if WITH_EDITOR

#include "HIEDComponentVisualizer.h"
#include "HowlOfIron/MapLogic/HISpawnPoint.h"
#include "HowlOfIron/MapLogic/HIComponentVisualizer.h"
#include "SceneManagement.h"

void FHIEDComponentVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	const UHIComponentVisualizer* componentVisualizer = Cast<const UHIComponentVisualizer>(Component);
	AHISpawnPoint* spawnPoint = Cast<AHISpawnPoint>(componentVisualizer->GetOwner());
	if (spawnPoint)
	{
		DrawCircle(PDI, spawnPoint->GetActorLocation(), FVector(1, 0, 0), FVector(0, 1, 0), componentVisualizer->drawColor, spawnPoint->radius, 20, 1);
	}
}

#endif
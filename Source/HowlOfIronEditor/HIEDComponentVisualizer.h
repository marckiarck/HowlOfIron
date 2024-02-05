// @AUTHOR: Carlos Fernandez

#pragma once

#include "ComponentVisualizer.h"

class FHIEDComponentVisualizer : public FComponentVisualizer
{
private:
	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;
};
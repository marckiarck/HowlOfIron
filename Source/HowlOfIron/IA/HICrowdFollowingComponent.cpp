// @AUTHOR: Guillermo


#include "IA/HICrowdFollowingComponent.h"
#include "Navigation/CrowdManager.h"

UHICrowdFollowingComponent::UHICrowdFollowingComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ECrowdSimulationState::Enabled;
}

UHICrowdFollowingComponent::~UHICrowdFollowingComponent()
{

}


// @AUTHOR: Guille, Carlos

#include "HIWall.h"
#include "Characters/VincentVolk/HIWerewolf.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineComponent.h"
#include "Components/BoxComponent.h"
#include "HIMacros.h"
#include "UI/HIButtonHUD.h"

AHIWall::AHIWall() :
	isClimbable(true),
	climbMinDistanceFromBorders(200.f),
	splineSeparation(60.f)
{
	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(sceneComponent);

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	boxComponent->SetupAttachment(sceneComponent);
	FVector scale = FVector(1.f, 4.f, 4.f);
	boxComponent->SetRelativeScale3D(scale);
	boxComponent->SetCollisionProfileName(COLLISION_WALL);
	boxComponent->SetNotifyRigidBodyCollision(true);

	climbingSpline = CreateDefaultSubobject<USplineComponent>(TEXT("ClimbingSpline"));
	climbingSpline->SetupAttachment(boxComponent);
	FVector center;
	FVector extent;
	GetActorBounds(true, center, extent);
	FVector bottomPoint = center;
	FVector topPoint = center;
	bottomPoint.Z = center.Z - extent.Z;
	topPoint.Z = center.Z + extent.Z;
	bottomPoint.X = center.X - splineSeparation;
	topPoint.X = bottomPoint.X;
	climbingSpline->SetWorldLocationAtSplinePoint(0, bottomPoint);
	climbingSpline->SetWorldLocationAtSplinePoint(1, topPoint);

	arrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	arrowComponent->SetupAttachment(boxComponent);
	arrowComponent->SetRelativeRotation(FVector(-1.f, 0.f, 0.f).Rotation());
}

void AHIWall::HIReload()
{
	RegisterAllComponents();

	FVector wallCenter;
	FVector wallExtent;
	GetActorBounds(true, wallCenter, wallExtent);
	float bottomZ = wallCenter.Z - wallExtent.Z;
	float topZ = wallCenter.Z + wallExtent.Z;

	FVector bottomPointLocation = climbingSpline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	FVector topPointLocation = climbingSpline->GetLocationAtSplinePoint(climbingSpline->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World);
	bottomPointLocation.Z = bottomZ;
	topPointLocation.Z = topZ;

	climbingSpline->SetWorldLocationAtSplinePoint(0, bottomPointLocation);
	climbingSpline->SetWorldLocationAtSplinePoint(climbingSpline->GetNumberOfSplinePoints() - 1, topPointLocation);
}

void AHIWall::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	HIReload();
}

void AHIWall::BeginPlay()
{
	Super::BeginPlay();

}

#include "Characters/Enemies/HIEnemyAccessory.h"
#include "HIMacros.h"
#include "Kismet/KismetMathLibrary.h"
#include "HIEnemy.h"

AHIEnemyAccessory::AHIEnemyAccessory() :
	isWeapon(false),
	isActive(true),
	droppable(false),
	dropAngle(0.f),
	dropImpulse(0.f)
{
	accessoryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AccessoryMesh"));
	SetRootComponent(accessoryMesh);
}

void AHIEnemyAccessory::HIDetach()
{
	if (droppable)
	{
		AHIEnemy* enemyAttached = Cast<AHIEnemy>(GetAttachParentActor());
		if (enemyAttached)
		{
			DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
			accessoryMesh->SetSimulatePhysics(true);
			accessoryMesh->AddForce(UKismetMathLibrary::RandomUnitVectorInConeInDegrees(enemyAttached->GetMesh()->GetUpVector(), dropAngle) * dropImpulse);
		}
	}
}

void AHIEnemyAccessory::HISetActive(bool _active)
{
	accessoryMesh->SetVisibility(_active);
	isActive = _active;
}

void AHIEnemyAccessory::HISetCollisionPreset(FName _collisionPresetName)
{
	accessoryMesh->SetCollisionProfileName(_collisionPresetName);
}

void AHIEnemyAccessory::HIAttachAccessoryToSocket(USkeletalMeshComponent* _skeletalMeshToAttach)
{
	if (_skeletalMeshToAttach)
	{
		accessoryMesh->AttachToComponent(_skeletalMeshToAttach, FAttachmentTransformRules::SnapToTargetNotIncludingScale, accessorySocketName);
	}
}

void AHIEnemyAccessory::BeginPlay()
{
	Super::BeginPlay();
}


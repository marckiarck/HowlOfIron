// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_SetRotationToActor.h"


UHITask_SetRotationToActor::UHITask_SetRotationToActor()
{

}

UHITask_SetRotationToActor* UHITask_SetRotationToActor::HISetRotationToActor(UGameplayAbility* OwningAbility, AActor* _actorToRotate)
{
    UHITask_SetRotationToActor* MyObj = NewAbilityTask<UHITask_SetRotationToActor>(OwningAbility);
    MyObj->actorToRotate = _actorToRotate;
    return MyObj;
}

void UHITask_SetRotationToActor::Activate()
{
    AActor* owner = GetAvatarActor();
    AHIEnemy* enemy = Cast<AHIEnemy>(owner);

    FVector targetLocation = actorToRotate->GetActorLocation();
    targetLocation.Z = enemy->GetActorLocation().Z;
    enemy->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(enemy->GetActorLocation(), targetLocation));


    EndTask();
}

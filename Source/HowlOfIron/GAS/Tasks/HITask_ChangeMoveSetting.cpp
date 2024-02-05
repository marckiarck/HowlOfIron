// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_ChangeMoveSetting.h"

UHITask_ChangeMoveSetting::UHITask_ChangeMoveSetting()
{

}

UHITask_ChangeMoveSetting* UHITask_ChangeMoveSetting::HIChangeMoveSetting(UGameplayAbility* OwningAbility, bool _setting)
{
    UHITask_ChangeMoveSetting* MyObj = NewAbilityTask<UHITask_ChangeMoveSetting>(OwningAbility);
    MyObj->setting=_setting;
    return MyObj;
}

void UHITask_ChangeMoveSetting::Activate()
{
AActor* owner =  GetAvatarActor();

AHIEnemy* enemy = Cast<AHIEnemy>(owner);

    enemy->GetCharacterMovement()->bOrientRotationToMovement = setting;
    enemy->bUseControllerRotationPitch = setting;
    enemy->bUseControllerRotationYaw = setting;
    enemy->bUseControllerRotationRoll = setting;

    EndTask();
}

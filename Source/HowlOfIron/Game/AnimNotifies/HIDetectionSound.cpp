// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AnimNotifies/HIDetectionSound.h"
#include "AbilitySystemComponent.h"
#include "Characters/HIAbilityCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameplayEffectTypes.h"
#include "Game/HIGameData.h"
#include "Game/PerceptionSystem/HIDetectorActorComponent.h"
#include "Game/DataTable/FHIWerewolfSound.h"
#include "HIMacros.h"

void UHIDetectionSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

    if (ValueDatatable)
    {
        FString ContextString = TEXT("Data table context");
        FHIWerewolfSound* Row = ValueDatatable->FindRow<FHIWerewolfSound>(rowName, ContextString, true);

        if (Row)
        {
            radius = Row->radius;
            force = Row->force;
            percentDiscountLowSteam = Row->percentDiscountLowSteam;
            percentDiscountHighSteam = Row->percentDiscountHighSteam;
            minumValue = Row->minumvalue;
        }
    }






    UWorld* affectedWorld = MeshComp->GetWorld();

    AHIAbilityCharacter* abilityCharacter = Cast<AHIAbilityCharacter>(MeshComp->GetOwner());
    if (!abilityCharacter)
    {
        return;
    }

    UAbilitySystemComponent* ownercomponent = abilityCharacter->GetAbilitySystemComponent();
    if (!ownercomponent)
    {
        return;
    }

    changeradius = radius;
    if (ownercomponent->HasMatchingGameplayTag(GET_GAMEPLAY_TAG(HIGHSTEAM_TAG)))
    {
        changeradius = radius * (1.f - percentDiscountHighSteam);
    }
    else if (ownercomponent->HasMatchingGameplayTag(GET_GAMEPLAY_TAG(LOWSTEAM_TAG)))
    {
        changeradius = radius * (1.f - percentDiscountLowSteam);
    }




    TArray<FHitResult> hitResults;
    TArray<AActor*> HitActors;
    FVector ownerpos = abilityCharacter->GetActorLocation();

    if (affectedWorld->SweepMultiByChannel(hitResults, ownerpos, ownerpos, FQuat::Identity, GAME_TRACE_ENEMY, FCollisionShape::MakeSphere(changeradius)))
    {
        for (FHitResult Iter : hitResults)
        {
            if (Iter.GetActor())
            {
                IAbilitySystemInterface* abilitySystemInterface = Cast<IAbilitySystemInterface>(Iter.GetActor());
                if (abilitySystemInterface)
                {
                    UAbilitySystemComponent* abilitycomp = abilitySystemInterface->GetAbilitySystemComponent();

                    if (abilitycomp)
                    {
                        HitActors.Add(Iter.GetActor());
                    }
                }
            }
        }

        if (UHIGameData::HIGetDebugMode())
        {
            DrawDebugSphere(affectedWorld, ownerpos, changeradius, 32.f, HIT_COLOR, false, 2.f);
        }

    }
    else if (UHIGameData::HIGetDebugMode())
    {
        DrawDebugSphere(affectedWorld, ownerpos, changeradius, 32.f, NO_HIT_COLOR, false, 2.f);
        return;
    }


    for (AActor* Iter : HitActors)
    {
        UAbilitySystemComponent* abilitycomp = Cast<IAbilitySystemInterface>(Iter)->GetAbilitySystemComponent();

        FVector targetpos = Iter->GetActorLocation();

        FVector OwnerTargetVector = targetpos - ownerpos;

        float magnitudeAudition = force * ((changeradius - (OwnerTargetVector.Size())) / changeradius);

        if (magnitudeAudition >= minumValue)
        {
            UGameplayEffect* effect = NewObject<UGameplayEffect>();
            CREATE_GAMEPLAYEFFECT(effect, EGameplayModOp::Additive, UHIDetectionAttributes::GetdetectionValueAttribute(), magnitudeAudition);
            abilitycomp->ApplyGameplayEffectToSelf(effect, 1, FGameplayEffectContextHandle());
            effect->ConditionalBeginDestroy();
        }
    }
}

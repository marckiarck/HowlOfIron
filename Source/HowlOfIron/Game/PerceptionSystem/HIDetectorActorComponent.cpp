#include "Game/PerceptionSystem/HIDetectorActorComponent.h"

// Sets default values for this component's properties
UHIDetectorActorComponent::UHIDetectorActorComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}



// Called when the game starts
void UHIDetectorActorComponent::BeginPlay()
{
    Super::BeginPlay();

    detectionValue = 0.f;

    detectionConfiguration = UHIDetectionConfiguration::HICreateDetectionConfiguration(initialDetectionConfiguration);

    gameplayeffect = NewObject<UGameplayEffect>();

    canDecrease = true;

    decreaseWaitTimer = 0.f;
}

void UHIDetectorActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
 
        FGameplayTagContainer tagcontainer;
        AActor* prueba = this->GetOwner();
        tagcontainer.AddTag(GET_GAMEPLAY_TAG(DEAD_TAG));
        tagcontainer.AddTag(GET_GAMEPLAY_TAG(ENEMY_DISABLE_TAG));
        tagcontainer.AddTag(GET_GAMEPLAY_TAG(STOP_BT_TAG));
        tagcontainer.AddTag(GET_GAMEPLAY_TAG(DISABLE_DISTANCE_TAG));


        if (!attachedAbilitySystem->HasAnyMatchingGameplayTags(tagcontainer))
        {
            HIUpdatedDetector(DeltaTime);
        }
    
}

void UHIDetectorActorComponent::HIUpdatedDetector(float DeltaTime)
{
    if (ensure(detectionConfiguration))
    {

        if (attachedAbilitySystem)
        {
            if (detectionAttributes->GetdetectionValue() != detectionValue)
            {
                canDecrease = false;
                decreaseWaitTimer = 0.f;
            }

            detectionValue = detectionAttributes->GetdetectionValue();
        }

        AActor* owner = GetOwner();
        UDetectionResult* resultDetection = detectionConfiguration->HIGetDetection(owner);
        //float calculedDetection = detectionConfiguration->HIGetDetection(GetOwner());
        float previousDetectionValue = detectionValue;


        if (resultDetection)
        {
            if (resultDetection->detectionValue != 0.f)
            {
                detectionValue = FMath::Min(100.f, detectionValue + resultDetection->detectionValue * DeltaTime);
                detectedActor = resultDetection->detectionActor;

                canDecrease = false;
                decreaseWaitTimer = 0.f;
            }
            else
            {
                if (canDecrease)
                {
                    detectionValue = FMath::Max(0.f, detectionValue - (detectionLostValue * DeltaTime));
                    detectedActor = nullptr;
                }
                else {
                    decreaseWaitTimer += DeltaTime;
                    if (decreaseWaitTimer >= 2.f)
                    {
                        canDecrease = true;
                        decreaseWaitTimer = 0.f;
                    }
                }
            }
        }
        else
        {
            if (canDecrease)
            {
                detectionValue = FMath::Max(0.f, detectionValue - (detectionLostValue * DeltaTime));
                detectedActor = nullptr;
            }
            else {
                decreaseWaitTimer += DeltaTime;
                if (decreaseWaitTimer >= 2.f)
                {
                    canDecrease = true;
                    decreaseWaitTimer = 0.f;
                }
            }
        }


        if (attachedAbilitySystem)
        {

            gameplayeffect->Modifiers.Empty();
            FGameplayModifierInfo modif = FGameplayModifierInfo();
            modif.ModifierOp = EGameplayModOp::Additive;
            modif.Attribute = detectionAttributes->GetdetectionValueAttribute();
            float detectionVariation = (detectionValue - previousDetectionValue);
            modif.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(detectionVariation));
            gameplayeffect->Modifiers.Add(modif);
            attachedAbilitySystem->ApplyGameplayEffectToSelf(gameplayeffect, 1, FGameplayEffectContextHandle());
        }

    }
}

void UHIDetectorActorComponent::HIAttachAbilitySystem(UAbilitySystemComponent* newAttachedAbilitySystem)
{
    attachedAbilitySystem = newAttachedAbilitySystem;
}

void UHIDetectorActorComponent::HIInitializeDetectionValue(UDataTable* abilityDataTable)
{
    detectionAttributes = Cast<UHIDetectionAttributes>(attachedAbilitySystem->InitStats(UHIDetectionAttributes::StaticClass(), abilityDataTable));
}

void UHIDetectorActorComponent::HISetDetectionConfiguration(UHIDetectionConfiguration* newDetectionConfiguration)
{
    detectionConfiguration = newDetectionConfiguration;
}

void UHIDetectorActorComponent::HISetDetectionConfiguration(UHIDetectionDataAsset* newDetectionAsset)
{
    detectionConfiguration = UHIDetectionConfiguration::HICreateDetectionConfiguration(newDetectionAsset);
}

void UHIDetectorActorComponent::HISetDetectionLostValue(float newDetectionLostValue)
{
    detectionLostValue = newDetectionLostValue;
}

void UHIDetectorActorComponent::HISetDetectionValue(float _newValue)
{
    detectionValue = _newValue;
}

AActor* UHIDetectorActorComponent::HIGetDetectedActor()
{
    return detectedActor;
}


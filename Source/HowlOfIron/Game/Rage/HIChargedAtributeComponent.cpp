// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Rage/HIChargedAtributeComponent.h"

// Sets default values for this component's properties
UHIChargedAttributeComponent::UHIChargedAttributeComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHIChargedAttributeComponent::BeginPlay()
{
    Super::BeginPlay();

    attributeChargedHeap = NewObject<UHIChargedHeap>();

    HIInitializeChargeHeap();

    elapsedDeltaTime = 0.f;

    // 	if (chargeLosTicktDelay != 0.f)
    // 	{
    // 		GetWorld()->GetTimerManager().SetTimer(UpdateChargedHeaptTimerHandle, this, &UHIChargedAttributeComponent::HIUpdateChargedHeap, chargeLosTicktDelay, true, chargeLosTicktDelay);
    // 	}
}


// Called every frame
void UHIChargedAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

   
        AActor* prueba = this->GetOwner();
        if (elapsedDeltaTime >= chargeLosTicktDelay)
        {
            elapsedDeltaTime -= chargeLosTicktDelay;
            HIUpdateChargedHeap();
        }
        elapsedDeltaTime += DeltaTime;
  
}

int UHIChargedAttributeComponent::HIGetMaxChargedValue()
{
    return maxChargedValueWeight;
}

void UHIChargedAttributeComponent::Activate(bool bReset /*= false*/)
{
    Super::Activate(bReset = false);

    chargeLosTicktDelay = chargeHeapdDataAsset->weightLostColdown;
}

void UHIChargedAttributeComponent::Deactivate()
{
    Super::Deactivate();

    chargeLosTicktDelay = MAX_FLT;
}

void UHIChargedAttributeComponent::HICalculateMaxChargedValueWeight()
{
    maxChargedValueWeight = 0.f;

    for (FChargeNodeConfiguration nodeConfiguration : chargeHeapdDataAsset->chargeNodeConfigurations)
    {
        maxChargedValueWeight += nodeConfiguration.chargeNodeFillValue;
    }
}

void UHIChargedAttributeComponent::HIInitializeChargeHeap()
{
    chargeLosTicktDelay = chargeHeapdDataAsset->weightLostColdown;
    attributeChargedHeap->HIInitialize(chargeHeapdDataAsset);
    HICalculateMaxChargedValueWeight();
    attributeChargedHeap->OnOverload.AddDynamic(this, &UHIChargedAttributeComponent::OverloadFunction);
}

void UHIChargedAttributeComponent::HIUpdateChargedHeap()
{
    if (attributeChargedHeap)
    {
        attributeChargedHeap->HITryDowngradeChargeNode(chargeHeapdDataAsset->WeightLostPerTick);
    }
}

void UHIChargedAttributeComponent::OverloadFunction()
{

}

void UHIChargedAttributeComponent::HIAttachAbilitySystem(UAbilitySystemComponent* abilitySystem)
{
    attributeChargedHeap->HIAttachAbilitySystem(abilitySystem);
}

int UHIChargedAttributeComponent::HIGetCurrentChargedValue()
{
    if (attributeChargedHeap)
    {
        return attributeChargedHeap->HIGetCurrentChargedValue();
    }

    return 0;
}

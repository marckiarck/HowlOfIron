// Guillermo Suárez

#include "UI/HIBossHUD.h"

bool UHIBossHUD::Initialize()
{
   Super::Initialize();

   isVulnerable = false;

   return true;
}

void UHIBossHUD::NativePreConstruct()
{
   Super::NativePreConstruct();


}

void UHIBossHUD::NativeConstruct()
{
   Super::NativePreConstruct();


}

void UHIBossHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	HIUpdateData();
}

void UHIBossHUD::HIInitAttributes(const class UHIEnemiesAttributes* _attributes) 
{
    maxHealth = _attributes->GetmaxHealth();
    health = _attributes->Gethealth();
    
    HICalculateHealthBar();
    HIUpdateData();
}

bool UHIBossHUD::HIGetvulnerability()
{
   return isVulnerable;
}

void UHIBossHUD::HISetVulnerability(bool _vulnerability)
{
   isVulnerable = _vulnerability;
   HIUpdateData();
}
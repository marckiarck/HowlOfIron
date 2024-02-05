// @AUTHOR: Guillermo Suárez


#include "UI/HIEnemyHUD.h"
#include "Characters/Enemies/HIEnemiesAttributes.h"
// #include <Math/UnrealMathUtility.h>

bool UHIEnemyHUD::Initialize()
{
    Super::Initialize();

    inAlertState = false;

    return true;
}

void UHIEnemyHUD::NativePreConstruct()
{
   Super::NativePreConstruct();

}

void UHIEnemyHUD::NativeConstruct()
{
   Super::NativeConstruct();

}

void UHIEnemyHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UHIEnemyHUD::HIInitAttributes(const class UHIEnemiesAttributes* _attributes)
{
    maxHealth = _attributes->GetmaxHealth();
    health = _attributes->Gethealth();
    maxFear = 100.f; 
    fear = _attributes->GetchargedValue();
    maxDetection = _attributes->GetmaxDetectionMeter();
    detection = 0.f;
    HICalculateHealthBar();
}

void UHIEnemyHUD::HIUpdateState()
{

    if (detection == 0.f)
    {
        HIChangeToPatrol();
        inAlertState = false;
        inCombatState = false;
        return;
    }

	if (detection >= 100.f && inCombatState == false)
	{
        HIChangeToCombat();
        inAlertState = false;
        inCombatState = true;
		return;
	}

    if (inAlertState == false)
    {
        HIChangeToAlert();
        inAlertState = true;
        inCombatState = false;
    }
    
}

float UHIEnemyHUD::HIGetMaxHealth()
{
    return maxHealth;
}

float UHIEnemyHUD::HIGetHealth()
{
    return health;
}

float UHIEnemyHUD::HIGetMaxFear()
{
    return maxFear;
}

float UHIEnemyHUD::HIGetFear()
{
    return fear;
}

float UHIEnemyHUD::HIGetMaxDetection()
{
	return maxDetection;
}

float UHIEnemyHUD::HIGetDetection()
{
	return detection;
}

void UHIEnemyHUD::HIChangeMaxHealth(float _maxHealth)
{
    maxHealth = _maxHealth;
    HICalculateHealthBar();
}

void UHIEnemyHUD::HIChangeHealth(float _health)
{
    health = _health;
    HICalculateHealthBar();
}

void UHIEnemyHUD::HIChangeMaxFear(float _maxFear)
{
    maxFear = _maxFear;
    HICalculateFearBar();
}

void UHIEnemyHUD::HIChangeFear(float _fear)
{
    fear = _fear;
    HICalculateFearBar();
}

void UHIEnemyHUD::HIChangeMaxDetection(float _maxDetection)
{
	maxDetection = _maxDetection;
}

void UHIEnemyHUD::HIChangeDetection(float _detection)
{
    float lastDetection = detection;
	detection = FMath::Clamp(_detection, 0.f, 100.f);

    if (detection != lastDetection)
    {
        HIUpdateState();
    }

    HICalculateDetectionIndicator();
}

void UHIEnemyHUD::HISetVulnerability(bool _val)
{

}

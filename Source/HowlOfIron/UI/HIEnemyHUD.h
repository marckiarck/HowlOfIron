// @AUTHOR: Guillermo Suárez
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HIEnemyHUD.generated.h"

class AHIEnemy;

UCLASS()
class HOWLOFIRON_API UHIEnemyHUD : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

    UPROPERTY(BlueprintReadOnly)
        float maxHealth;

    UPROPERTY(BlueprintReadOnly)
        float health;

    UPROPERTY(BlueprintReadOnly)
        float maxFear;

    UPROPERTY(BlueprintReadOnly)
        float fear;

    UPROPERTY(BlueprintReadOnly)
        float maxDetection;

    UPROPERTY(BlueprintReadOnly)
        float detection;

    UPROPERTY(BlueprintReadWrite)
        bool disabled = false;

protected:


private:

    UPROPERTY(VisibleAnywhere)
        bool inAlertState;

    UPROPERTY(VisibleAnywhere)
        bool inCombatState;


public:
    
    virtual void HIInitAttributes(const class UHIEnemiesAttributes* _attributes);

    UFUNCTION(BlueprintImplementableEvent)
        void HICalculateHealthBar();

    UFUNCTION(BlueprintImplementableEvent)
        void HICalculateFearBar();

    UFUNCTION(BlueprintImplementableEvent)
        void HICalculateDetectionIndicator();

    UFUNCTION(BlueprintImplementableEvent)
        void HIChangeToCombat();

    UFUNCTION(BlueprintImplementableEvent)
        void HIChangeToAlert();

    UFUNCTION(BlueprintImplementableEvent)
        void HIChangeToPatrol();

    UFUNCTION(BlueprintImplementableEvent)
        void HIDisableHUD();

    UFUNCTION()
        float HIGetMaxHealth();

    UFUNCTION()
        float HIGetHealth();

    UFUNCTION()
        float HIGetMaxFear();

    UFUNCTION()
        float HIGetFear();

    UFUNCTION()
        float HIGetMaxDetection();

    UFUNCTION()
        float HIGetDetection();

    UFUNCTION()
        void HIChangeMaxHealth(float _maxHealth);

    UFUNCTION()
        void HIChangeHealth(float _health);

    UFUNCTION()
        void HIChangeMaxFear(float _maxFear);

    UFUNCTION()
        void HIChangeFear(float _fear);

    UFUNCTION()
        void HIChangeMaxDetection(float _maxDetection);

    UFUNCTION()
        void HIChangeDetection(float _detection);

    UFUNCTION()
        virtual void HISetVulnerability(bool _val);

    UFUNCTION(BlueprintImplementableEvent)
        void HIUpdateData();

protected:


private:
    UFUNCTION()
        void HIUpdateState();

};

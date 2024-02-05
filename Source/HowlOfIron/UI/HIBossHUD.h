// Guillermo Suárez
#pragma once

#include "CoreMinimal.h"
#include "UI/HIEnemyHUD.h"
#include "HIBossHUD.generated.h"

UCLASS()
class HOWLOFIRON_API UHIBossHUD : public UHIEnemyHUD
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:


protected:


private:
    UPROPERTY()
        bool isVulnerable;

public:
    virtual void HIInitAttributes(const class UHIEnemiesAttributes* _attributes) override;

    UFUNCTION(BlueprintCallable, BlueprintPure)
        bool HIGetvulnerability();

    virtual void HISetVulnerability(bool _val) override;

protected:


private:


};

// @AUTHOR: Guillermo Suárez

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "HISteamTrigger.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API AHISteamTrigger : public ATriggerBox
{
    GENERATED_BODY()

public:
    AHISteamTrigger(const FObjectInitializer& ObjectInitializer);

public:
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara system")
    // 	UNiagaraComponent* niagaraComponent; 

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
        bool isActive;

    UPROPERTY(EditAnywhere)
        bool cycle = false;


    UPROPERTY(EditAnywhere, meta = (EditCondition = "cycle == true", EditConditionHides))
        float timeDeactivated = 2.f;

    UPROPERTY(EditAnywhere, meta = (EditCondition = "cycle == true", EditConditionHides))
        float timeActivated = 2.f;


protected:


private:
    UPROPERTY()
        float elapsedActived;
    UPROPERTY()
        float elapsedDeactivated;

public:

    UFUNCTION(BlueprintCallable)
        void HIEnemiesLostVision();


    UFUNCTION(BlueprintCallable)
        void HIActivateSteam(float _time);


    UFUNCTION(BlueprintCallable)
        void HIDeactivateSteam();

    UFUNCTION(BlueprintImplementableEvent)
        void HIActivationChange();


    UFUNCTION(BlueprintImplementableEvent)
        void HIDeactivationChange();

protected:


private:

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

};

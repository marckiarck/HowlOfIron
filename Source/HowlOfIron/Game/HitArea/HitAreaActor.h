// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "HitAreaActor.generated.h"

#define END_POSITION_VARIABLE "User.BeamEndPos"
#define START_POSITION_VARIABLE "User.BeamStartPos"
#define HIT_AREA_COLOR_VARIABLE "User.LaserColor"
#define COLOR_R_VARIABLE "User.ColorR"
#define COLOR_G_VARIABLE "User.ColorG"
#define COLOR_B_VARIABLE "User.ColorB"
#define LOOP_DURATION_VARIABLE "User.LoopDuration"
#define ELAPSED_TIME_VARIABLE "User.ElapsedTime"
#define ROTATION_VARIABLE "User.Rotation"
#define ROTATION_SPEED_VARIABLE "User.RotationSpeed"

UENUM()
enum FollowMode {
	STOP_WHEN_AIM_ENDS,
	NEVER_STOP
};

UENUM()
enum ParticleKillMode {
	NORMAL_KILL,
	KILL_WHEN_STOP_AIM
};

UENUM()
enum HIHitAreaSpawnMode {
	ATTACHED,
	LOCATION
};

UCLASS()
class HOWLOFIRON_API AHIHitAreaActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHIHitAreaActor();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitArea")
		UNiagaraSystem* niagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitArea", meta = (DisplayName = "Area Follow Mode"))
		TEnumAsByte<FollowMode> followMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitArea", meta = (DisplayName = "Area Spawn Mode"))
		TEnumAsByte<HIHitAreaSpawnMode> spawnMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitArea", meta = (DisplayName = "Kill Particle Mode"))
		TEnumAsByte<ParticleKillMode> killMode = NORMAL_KILL;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitArea", meta = (DisplayName = "Direct Shoot"))
		bool directShoot;

	UPROPERTY(EditAnywhere, Category = "HitArea")
		float lifeTime;

	UPROPERTY(EditAnywhere, Category = "HitArea")
		float colorChangeDuration;

	float rayLength;

	AActor* hitObjetive;

	FVector attachOffset;

	FVector DirectionShootPoint;

	bool hitAreaAimActived;


private:

	USceneComponent* hitAreaEmiter;
	FName emiterSocketName;

	float elapsedLifeTime;

	UPROPERTY(Transient)
		UNiagaraComponent* niagaraParticleComponent;

	UPROPERTY(VisibleAnywhere)
	FLinearColor hitAreaColor;

	float lastFrameRotation;

public:
	void HISetEmiter(USceneComponent* emiter, FName emiterSocket);
	virtual void Tick(float DeltaTime) override;
	void StopHitArea();

protected:
	virtual void BeginPlay() override;

	void HIInitializeNiagaraSystem();

	private:
		void HIUpdateNiagaraParameters();
		void HIUpdateNiagaraRotation();

};

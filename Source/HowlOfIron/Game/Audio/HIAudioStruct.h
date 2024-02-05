// Created by Pablo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Sound/SoundCue.h"
#include "Components/SceneComponent.h"
#include "HIAudioStruct.generated.h"


USTRUCT(BlueprintType)
struct HOWLOFIRON_API FHIAudioStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FHIAudioStruct();
	~FHIAudioStruct() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundCue* sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float volume = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float pitch = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundAttenuation* attenuation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundConcurrency* concurrency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float startTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isUISound = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool autoDestroy = true;
};

UCLASS(BlueprintType, Blueprintable)
class UHIAudio : public UObject
{
	GENERATED_BODY()

public:
	UHIAudio() = default;
	~UHIAudio() {};

	UFUNCTION(BlueprintCallable, Category = "Anything")
		static void HIUseSound2D(AActor* _owningActor, FDataTableRowHandle _SoundRow);

    UFUNCTION(BlueprintCallable, Category = "Anything")
        static UAudioComponent* HICreateSound2D(UObject* _world, FDataTableRowHandle _SoundRow);

	UFUNCTION(BlueprintCallable, Category = "Anything")
		static void HIUseSound3D(AActor* _owningActor, FVector _worldLoc, FDataTableRowHandle _soundRow);

	UFUNCTION(BlueprintCallable, Category = "Anything")
		static void HIUseSoundAttached(USceneComponent* _attachToComponent, FVector _worldLocation, FDataTableRowHandle _soundRow, FName _boneAttach);

	UFUNCTION(BlueprintCallable, Category = "Anything" )
		static void HIPlayDialogue(AActor* dialogueOwner, FDataTableRowHandle _soundRow, UHIDelegateCondition* stopCondition);
};

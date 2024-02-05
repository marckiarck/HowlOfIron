// Created by Pablo


#include "Game/Audio/HIAudioStruct.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Game/HIGameData.h"
#include "Components/AudioComponent.h"
#include "Engine/DataTable.h"
#include "../VoiceActors/HIDialogueComponent.h"
#include "MapLogic/HIObjectPooler_Actors.h"

void UHIAudio::HIUseSound2D(AActor* _owningActor, FDataTableRowHandle _soundRow)
{
	FString ContextString = TEXT("Data table context");
	FHIAudioStruct* Row = nullptr;

	Row = _soundRow.DataTable->FindRow<FHIAudioStruct>(_soundRow.RowName, ContextString, true);

	if (Row && UHIGameData::HIGetWerewolfWorld())
	{
		UGameplayStatics::PlaySound2D(UHIGameData::HIGetWerewolfWorld(), Row->sound, Row->volume, Row->pitch, Row->startTime,
			Row->concurrency, _owningActor);
	}
}

UAudioComponent* UHIAudio::HICreateSound2D(UObject* _world, FDataTableRowHandle _SoundRow)
{

	FString ContextString = TEXT("Data table context");
	FHIAudioStruct* Row = nullptr;

	Row = _SoundRow.DataTable->FindRow<FHIAudioStruct>(_SoundRow.RowName, ContextString, true);

	if (Row)
	{
		return UGameplayStatics::CreateSound2D(_world, Row->sound, Row->volume, Row->pitch, Row->startTime, Row->concurrency, true, false);
	}
	return nullptr;
}

void UHIAudio::HIUseSound3D(AActor* _owningActor, FVector _worldLocation, FDataTableRowHandle _soundRow)
{
	FString ContextString = TEXT("Data table context");
	FHIAudioStruct* Row = nullptr;

	Row = _soundRow.DataTable->FindRow<FHIAudioStruct>(_soundRow.RowName, ContextString, true);

	if (Row && UHIGameData::HIGetWerewolfWorld())
	{
		UGameplayStatics::PlaySoundAtLocation(UHIGameData::HIGetWerewolfWorld(), Row->sound, _worldLocation, FRotator::ZeroRotator,
			Row->volume, Row->pitch, Row->startTime, Row->attenuation, Row->concurrency, _owningActor);
	}
}

void UHIAudio::HIUseSoundAttached(USceneComponent* _attachToComponent, FVector _worldLoc, FDataTableRowHandle _soundRow, FName _boneAttach)
{
	FString ContextString = TEXT("Data table context");
	FHIAudioStruct* Row = nullptr;

	Row = _soundRow.DataTable->FindRow<FHIAudioStruct>(_soundRow.RowName, ContextString, true);


	if (Row)
	{
		UGameplayStatics::SpawnSoundAttached(Row->sound, _attachToComponent, _boneAttach, _worldLoc, FRotator::ZeroRotator,
			EAttachLocation::KeepWorldPosition, false, Row->volume, Row->pitch, Row->startTime, Row->attenuation,
			Row->concurrency, Row->autoDestroy);
	}
}

void UHIAudio::HIPlayDialogue(AActor* dialogueOwner, FDataTableRowHandle _soundRow, UHIDelegateCondition* stopCondition)
{
	FString ContextString = TEXT("Data table context");
	FHIAudioStruct* Row = nullptr;

	Row = _soundRow.DataTable->FindRow<FHIAudioStruct>(_soundRow.RowName, ContextString, true);

	if (dialogueOwner && Row)
	{
		AHIDialogueComponent* dialogueComponent = Cast<AHIDialogueComponent>(AHIObjectPooler_Actors::HIGetObjectPooler(UHIGameData::HIGetWerewolfWorld())->GetObjectFromPool(AHIDialogueComponent::StaticClass(), dialogueOwner));
		dialogueComponent->HIInitilize();
		dialogueComponent->HISetUpConfiguration(*Row);
		dialogueComponent->AttachToActor(dialogueOwner, FAttachmentTransformRules::KeepRelativeTransform);

		if (stopCondition)
		{
			dialogueComponent->HIAttachStopCondition(stopCondition);
		}

		dialogueComponent->HIPlayDialogue();
	}
}

FHIAudioStruct::FHIAudioStruct() :
	sound(nullptr),
	attenuation(nullptr),
	concurrency(nullptr)
{

}

// Copyright Emran Tokhi 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActiveActors() const;
	void GetAudioComponent();
	void PlaySound();
	void CheckForEmptyPointers() const;

private:
	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpenedTime = 0.f;
	bool bDoorHasBeenOpened = false;
	bool bDoorHasBeenClosed = true;

	UPROPERTY();
	UAudioComponent* AudioComponent = nullptr;

	UPROPERTY(EditAnywhere);
	float TargetYaw = 100.0f; 

	UPROPERTY(EditAnywhere);
	float OpenSpeed = 1.5f;
	
	UPROPERTY(EditAnywhere);
	float CloseSpeed = 1.5f;

	UPROPERTY(EditAnywhere);
	float TimeLeftOpen = 2.f;

	UPROPERTY(EditAnywhere);
	ATriggerVolume* PressurePlate = nullptr;
	
	UPROPERTY(EditAnywhere);
	float MassToOpenDoor = 50.f;
};

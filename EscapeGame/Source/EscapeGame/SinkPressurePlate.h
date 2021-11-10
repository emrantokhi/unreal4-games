// Copyright Emran Tokhi 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/PlayerController.h"
#include "SinkPressurePlate.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPEGAME_API USinkPressurePlate : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USinkPressurePlate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SinkPlate(float DeltaTime);
	void LiftPlate(float DeltaTime);
	float TotalMassOfActiveActors() const;

private:
	float InitialHeight;
	float SinkTarget;

	float TimeSteppedOn = 0.f;

	UPROPERTY(EditAnywhere);
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere);
	float SinkAmount = 10.f;

	UPROPERTY(EditAnywhere);
	float SinkSpeed = 2.0f;

	UPROPERTY(EditAnywhere);
	float TimeBeforeRising = 2.0f;

	UPROPERTY(EditAnywhere);
	float TotalMassToSink = 50.f;
};
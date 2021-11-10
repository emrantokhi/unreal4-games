// Copyright Emran Tokhi 2021

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"

#define OUT

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Grab();
	void Release();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void FindPhysicsHandle();
	void SetupInputs();
	//Updates the value for LineTraceEnd, PVPL, and PVPR
	void RecalculateLineTraceEnd();
	//Returns an actor that has a physics body thru ray casting
	FHitResult FindFirstActorInReach();

	UPROPERTY();
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY();
	UInputComponent* InputHandle = nullptr;

	FVector LineTraceEnd;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	UPROPERTY(EditAnywhere);
	float ReachLength = 200.f;
	
	UPROPERTY(EditAnywhere);
	float DebugLineThickness = 3.f;
};

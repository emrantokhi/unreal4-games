// Copyright Emran Tokhi 2021


#include "RatSpin.h"

// Sets default values for this component's properties
URatSpin::URatSpin()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void URatSpin::BeginPlay()
{
	Super::BeginPlay();

	//Setting the actor's Yaw to 0, since it'll be spinning anyways
	//So initial rotation spot most likely wont matter
	FRotator CurrentMouseRotation = GetOwner()->GetActorRotation();
	CurrentMouseRotation.Yaw = 0.f;
	GetOwner()->SetActorRotation(CurrentMouseRotation);
}


// Called every frame
void URatSpin::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	RotateMouse(DeltaTime);
}

void URatSpin::RotateMouse(float DeltaTime) {
	FRotator CurrentMouseRotation = GetOwner()->GetActorRotation();
	
	if (CurrentMouseRotation.Yaw + RotateSpeed > 360.f) {
		CurrentMouseRotation.Yaw = CurrentMouseRotation.Yaw + RotateSpeed - 360.f;
	}

	CurrentMouseRotation.Yaw = FMath::FInterpTo(CurrentMouseRotation.Yaw, CurrentMouseRotation.Yaw + RotateSpeed, DeltaTime, RotateSpeed);
	
	GetOwner()->SetActorRotation(CurrentMouseRotation);
}
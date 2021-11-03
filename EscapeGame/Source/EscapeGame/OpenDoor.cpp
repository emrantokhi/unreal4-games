// Copyright Emran Tokhi 2021


#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += InitialYaw;

	//Error message if no pressure plate set
	if (!PressurePlate) {
		UE_LOG(LogTemp, Warning, TEXT("%s has door component, but no pressure plate set."), *GetOwner()->GetName());
	}

	//Set the player's pawn as the actor
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor(DeltaTime);
		DoorLastOpenedTime = GetWorld()->GetTimeSeconds();
	}
	else if (PressurePlate && !PressurePlate->IsOverlappingActor(ActorThatOpens) && (GetWorld()->GetTimeSeconds() - DoorLastOpenedTime >= TimeLeftOpen)) {
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime) {
	//Get the rotation
	FRotator SetRotation = GetOwner()->GetActorRotation();
	//Change the yaw based on the current yaw and interp function
	SetRotation.Yaw = FMath::FInterpTo(SetRotation.Yaw, TargetYaw, DeltaTime, OpenSpeed);

	GetOwner()->SetActorRotation(SetRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime) {
	GetWorld()->GetTimeSeconds();
	//Get the rotation
	FRotator SetRotation = GetOwner()->GetActorRotation();
	//Change the yaw based on the current yaw and interp function
	SetRotation.Yaw = FMath::FInterpTo(SetRotation.Yaw, InitialYaw, DeltaTime, CloseSpeed);

	GetOwner()->SetActorRotation(SetRotation);
}
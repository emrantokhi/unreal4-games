// Copyright Emran Tokhi 2021


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	TargetYaw += GetOwner()->GetActorRotation().Yaw;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get the rotation
	FRotator SetRotation = GetOwner()->GetActorRotation();
	//Change the yaw based on the current yaw and interp function
	SetRotation.Yaw = FMath::FInterpTo(SetRotation.Yaw, TargetYaw, DeltaTime, 2.f);
	
	GetOwner()->SetActorRotation(SetRotation);
}


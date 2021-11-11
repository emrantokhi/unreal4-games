// Copyright Emran Tokhi 2021


#include "LiftDoor.h"

// Sets default values for this component's properties
ULiftDoor::ULiftDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void ULiftDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorLocation().Z;
	TargetYaw += InitialYaw;

	GetAudioComponent();
	CheckForEmptyPointers();
}

// Called every frame
void ULiftDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate && PressurePlate2) {
		if (TotalMassOfActiveActors() > MassToOpenDoor) {
			OpenDoor(DeltaTime);
			DoorLastOpenedTime = GetWorld()->GetTimeSeconds();
		}
		else if ((GetWorld()->GetTimeSeconds() - DoorLastOpenedTime >= TimeLeftOpen)) {
			CloseDoor(DeltaTime);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s has OpenDoor component, but no pressure plate set."), *GetOwner()->GetName());
	}
}

void ULiftDoor::OpenDoor(float DeltaTime) {
	//AudioComponent->Stop();
	//Get the rotation
	FVector LiftDoor = GetOwner()->GetActorLocation();
	//Change the yaw based on the current yaw and interp function
	LiftDoor.Z = FMath::FInterpTo(LiftDoor.Z, TargetYaw, DeltaTime, OpenSpeed);

	GetOwner()->SetActorLocation(LiftDoor);
	if (!bDoorHasBeenOpened) {
		PlaySound();
		bDoorHasBeenOpened = true;
		bDoorHasBeenClosed = false;
	}
}

void ULiftDoor::CloseDoor(float DeltaTime) {
	//AudioComponent->Stop();
	GetWorld()->GetTimeSeconds();
	//Get the rotation
	FVector CloseDoor = GetOwner()->GetActorLocation();
	//Change the yaw based on the current yaw and interp function
	CloseDoor.Z = FMath::FInterpTo(CloseDoor.Z, InitialYaw, DeltaTime, CloseSpeed);

	GetOwner()->SetActorLocation(CloseDoor);
	if (!bDoorHasBeenClosed) {
		PlaySound();
		bDoorHasBeenOpened = false;
		bDoorHasBeenClosed = true;
	}
}

float ULiftDoor::TotalMassOfActiveActors() const {
	float TotalMass = 0.f;

	if (!PressurePlate || !PressurePlate2) { return -1.f; }

	TArray<AActor*> OverlappingActorsFirstPlate;
	TArray<AActor*> OverlappingActorsSecondPlate;
	PressurePlate->GetOverlappingActors(OUT OverlappingActorsFirstPlate);
	PressurePlate2->GetOverlappingActors(OUT OverlappingActorsSecondPlate);

	for (AActor* TempActor : OverlappingActorsFirstPlate) {
		TotalMass += TempActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	for (AActor* TempActor : OverlappingActorsSecondPlate) {
		TotalMass += TempActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void ULiftDoor::GetAudioComponent() {
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
}

void ULiftDoor::PlaySound() {
	if (AudioComponent) {
		if (!AudioComponent->IsPlaying()) {
			AudioComponent->Play(0.f);
		}
	}
}

void ULiftDoor::CheckForEmptyPointers() const {
	//Error message if no pressure plate set
	if (!PressurePlate || !PressurePlate2) {
		UE_LOG(LogTemp, Warning, TEXT("%s has OpenDoor component, but no pressure plate set."), *GetOwner()->GetName());
	}
	if (!AudioComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s has an OpenDoor component, but no audio component."), *GetOwner()->GetName());
	}
	else if (!AudioComponent->Sound) {
		UE_LOG(LogTemp, Warning, TEXT("%s has an audio component, but no sound attached."), *GetOwner()->GetName());
	}
}
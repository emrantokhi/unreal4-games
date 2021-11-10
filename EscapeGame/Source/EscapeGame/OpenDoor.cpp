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
	
	GetAudioComponent();
	CheckForEmptyPointers();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate) {
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

void UOpenDoor::OpenDoor(float DeltaTime) {
	//AudioComponent->Stop();
	//Get the rotation
	FRotator SetRotation = GetOwner()->GetActorRotation();
	//Change the yaw based on the current yaw and interp function
	SetRotation.Yaw = FMath::FInterpTo(SetRotation.Yaw, TargetYaw, DeltaTime, OpenSpeed);

	GetOwner()->SetActorRotation(SetRotation);
	if (!bDoorHasBeenOpened) {
		PlaySound();
		bDoorHasBeenOpened = true;
		bDoorHasBeenClosed = false;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime) {
	//AudioComponent->Stop();
	GetWorld()->GetTimeSeconds();
	//Get the rotation
	FRotator SetRotation = GetOwner()->GetActorRotation();
	//Change the yaw based on the current yaw and interp function
	SetRotation.Yaw = FMath::FInterpTo(SetRotation.Yaw, InitialYaw, DeltaTime, CloseSpeed);

	GetOwner()->SetActorRotation(SetRotation);
	if (!bDoorHasBeenClosed) {
		PlaySound();
		bDoorHasBeenOpened = false;
		bDoorHasBeenClosed = true;
	}
}

float UOpenDoor::TotalMassOfActiveActors() const {
	float TotalMass = 0.f;

	if (!PressurePlate) { return -1.f; }
	
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	
	for (AActor* TempActor : OverlappingActors) {
		TotalMass += TempActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return TotalMass;
}

void UOpenDoor::GetAudioComponent() {
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
}

void UOpenDoor::PlaySound() {
	if (AudioComponent) {
		if (!AudioComponent->IsPlaying()) {
			AudioComponent->Play(0.f);
		}
	}
}

void UOpenDoor::CheckForEmptyPointers() const {
	//Error message if no pressure plate set
	if (!PressurePlate) {
		UE_LOG(LogTemp, Warning, TEXT("%s has OpenDoor component, but no pressure plate set."), *GetOwner()->GetName());
	}
	if (!AudioComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s has an OpenDoor component, but no audio component."), *GetOwner()->GetName());
	}
	else if (!AudioComponent->Sound) {
		UE_LOG(LogTemp, Warning, TEXT("%s has an audio component, but no sound attached."), *GetOwner()->GetName());
	}
}
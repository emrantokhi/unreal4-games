// Copyright Emran Tokhi 2021


#include "SinkPressurePlate.h"

// Sets default values for this component's properties
USinkPressurePlate::USinkPressurePlate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USinkPressurePlate::BeginPlay()
{
	Super::BeginPlay();

	InitialHeight = GetOwner()->GetActorLocation().Z;
	SinkTarget = InitialHeight - SinkAmount;

	//Error message if no pressure plate set
	if (!PressurePlate) {
		UE_LOG(LogTemp, Warning, TEXT("%s has OpenDoor component, but no pressure plate set."), *GetOwner()->GetName());
	}
}

// Called every frame
void USinkPressurePlate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate) {
		if (TotalMassOfActiveActors() > TotalMassToSink) {
			SinkPlate(DeltaTime);
			TimeSteppedOn = GetWorld()->GetTimeSeconds();
		}
		else if ((TotalMassOfActiveActors() < TotalMassToSink) &&
			(GetWorld()->GetTimeSeconds() - TimeSteppedOn >= TimeBeforeRising)) {
			LiftPlate(DeltaTime);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s has OpenDoor component, but no pressure plate set."), *GetOwner()->GetName());
	}
}

void USinkPressurePlate::SinkPlate(float DeltaTime) {
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	CurrentLocation.Z = FMath::FInterpTo(CurrentLocation.Z, SinkTarget, DeltaTime, SinkSpeed);

	GetOwner()->SetActorLocation(CurrentLocation);
}

void USinkPressurePlate::LiftPlate(float DeltaTime) {
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	CurrentLocation.Z = FMath::FInterpTo(CurrentLocation.Z, InitialHeight, DeltaTime, SinkSpeed);

	GetOwner()->SetActorLocation(CurrentLocation);
}

float USinkPressurePlate::TotalMassOfActiveActors() const {
	float TotalMass = 0.f;

	if (!PressurePlate) { return -1.f; }

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* TempActor : OverlappingActors) {
		TotalMass += TempActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}
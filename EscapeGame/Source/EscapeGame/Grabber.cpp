// Copyright Emran Tokhi 2021


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();

	SetupInputs();
}

void UGrabber::FindPhysicsHandle() {
	//Check for Physics handle component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("%s does not include a physics handle!"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputs() {
	//Grab the input component
	InputHandle = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputHandle) {
		InputHandle->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputHandle->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::RecalculateLineTraceEnd() {
	//Get the players viewpoint (where its pointing)
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * ReachLength;
}

FHitResult UGrabber::FindFirstActorInReach() {
	FHitResult ObjectInRayCast;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	RecalculateLineTraceEnd();

	//Ray-cast out to a certain distance (to reach out and grab something)
	GetWorld()->LineTraceSingleByObjectType(
		OUT ObjectInRayCast,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return ObjectInRayCast;
}

void UGrabber::Grab() {
	RecalculateLineTraceEnd();
	//Only raycast when key is pressed
	FHitResult ActorInReach = FindFirstActorInReach();
	UPrimitiveComponent* ComponentToGrab = ActorInReach.GetComponent();
	AActor* ActorHit = ActorInReach.GetActor();

	if (ActorHit) {
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd
		);
	}
}

void UGrabber::Release() {
	//Remove/release attached component
	if (PhysicsHandle) {
		PhysicsHandle->ReleaseComponent();
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent) {
		RecalculateLineTraceEnd();
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}
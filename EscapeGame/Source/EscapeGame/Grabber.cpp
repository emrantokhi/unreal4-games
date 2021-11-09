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

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Button pressed for grabber."));
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	FVector LineTraceEnd;

	//Get the players viewpoint (where its pointing)
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * ReachLength;
	//Only raycast when key is pressed
	FHitResult ActorInReach = FindFirstActorInReach();

	UPrimitiveComponent* ComponentToGrab = ActorInReach.GetComponent();

	//If ActorInReach is not empty, then grab the item
	if (ActorInReach.GetActor()) {
		//If we hit something, then attach physics handle
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd
		);
	}
}

FVector* UGrabber::CalculateLineTraceEnd(FVector& OUT PlayerViewPointLocation, FRotator& OUT PlayerViewPointRotation) {
	return nullptr;
}

FHitResult UGrabber::FindFirstActorInReach() {
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	FVector LineTraceEnd;

	//Get the players viewpoint (where its pointing)
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * ReachLength;

	FHitResult ObjectInRayCast;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

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

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Button released for grabber"));
	//Remove/release physics handle
	if (PhysicsHandle) {
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::FindPhysicsHandle() {
	//Check for Physics handle component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		//PhysicsHandle has been found
	}
	else {
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

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if physics handle is attached
		//keep moving the object we are holding
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	FVector LineTraceEnd;

	//Get the players viewpoint (where its pointing)
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * ReachLength;
	
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

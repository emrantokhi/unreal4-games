// Copyright Emran Tokhi 2021


#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Check for Physics handle component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		//PhysicsHandle has been found
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s does not include a physics handle!"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	//Get the players viewpoint (where its pointing)
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	//Log it
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s\nRotation: %s"),
	//	*PlayerViewPointLocation.ToString(),
	//	*PlayerViewPointRotation.ToString()
	//);

	//Draw a line from player showing the reach 
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * ReachLength;
	
	DrawDebugLine(
		GetWorld(), 
		PlayerViewPointLocation, 
		LineTraceEnd, 
		FColor::Purple, 
		true, 
		-1.f, 
		(uint8)1U, 
		DebugLineThickness
	);

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
	
	//See what the raycast hit
		//Is it something we can actually pick up?
	if(ObjectInRayCast.GetActor()) {
		UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *ObjectInRayCast.GetActor()->GetName());
	}
}


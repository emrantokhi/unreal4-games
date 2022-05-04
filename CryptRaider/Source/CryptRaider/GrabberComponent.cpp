// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();	
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector NewLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(NewLocation, GetComponentRotation());
	}
}

void UGrabberComponent::Released()
{
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabberComponent::Grab()
{
	FHitResult Hit;

	if (GetGrabbableInReach(Hit))
	{
		Hit.GetComponent()->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			Hit.GetComponent(),
			NAME_None,
			Hit.ImpactPoint,
			GetComponentRotation()
		);
	}

}

bool UGrabberComponent::GetGrabbableInReach(FHitResult& OutHit) const
{
	if (!PhysicsHandle)
	{
		return false;
	}

	FVector End = GetComponentLocation() + GetForwardVector() * LineTraceLength;

	return GetWorld()->SweepSingleByChannel(
		OutHit,
		GetComponentLocation(),
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(GrabRadius));
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatorComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
URotatorComponent::URotatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotatorComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialRotation = GetOwner()->GetActorRotation();
}


// Called every frame
void URotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator TargetRotation = InitialRotation;

	if (bShouldRotate)
	{
		TargetRotation = RotationOffset + InitialRotation;
	}

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, InterpSpeed);
	GetOwner()->SetActorRotation(CurrentRotation);
}

void URotatorComponent::SetShouldRotate(bool Rotate)
{
	bShouldRotate = Rotate;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "MoverComponent.h"
#include "RotatorComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

//Get the actor with the correct tag
AActor* UTriggerComponent::GetAcceptableActor() 
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors) {
		if (Actor->ActorHasTag(TagName))
		{
			bHasAcceptableActor = true;
			return Actor;
		}
	}

	bHasAcceptableActor = false;
	return nullptr;
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();

	if (!bIsDoubleTrigger)
	{
		if (MoverComponent)
		{
			MoverComponent->SetShouldMove(MoverComponent && Actor);
		}
	
		if (RotatorComponents.Num() > 0)
		{
			for (URotatorComponent* Rotator : RotatorComponents)
			{
				Rotator->SetShouldRotate((RotatorComponents.Num() > 0) && Actor);
			}
		}
	}
}

void UTriggerComponent::SetMover(UMoverComponent* Mover)
{
	MoverComponent = Mover;
}

void UTriggerComponent::AddRotator(URotatorComponent* NewRotator)
{
	RotatorComponents.Add(NewRotator);
}

bool UTriggerComponent::HasAcceptableActor() const
{
	return bHasAcceptableActor;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DoubleTriggerComponent.h"
#include "TriggerComponent.h"
#include "MoverComponent.h"

UDoubleTriggerComponent::UDoubleTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoubleTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	
	if (OtherTrigger && MoverComponent)
	{
		MoverComponent->SetShouldMove(Actor && OtherTrigger->HasAcceptableActor());
	}
}

void UDoubleTriggerComponent::SetMover(UMoverComponent* Mover)
{
	MoverComponent = Mover;
}

void UDoubleTriggerComponent::SetOtherTrigger(UTriggerComponent* Trigger)
{
	OtherTrigger = Trigger;
}

//Get the actor with the correct tag
AActor* UDoubleTriggerComponent::GetAcceptableActor()
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors) {
		if (Actor->ActorHasTag(TagName))
		{
			return Actor;
		}
	}

	return nullptr;
}
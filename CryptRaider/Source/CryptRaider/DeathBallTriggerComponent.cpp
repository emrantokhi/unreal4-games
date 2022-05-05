// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathBallTriggerComponent.h"

// Sets default values for this component's properties
UDeathBallTriggerComponent::UDeathBallTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDeathBallTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UDeathBallTriggerComponent::GetAcceptableActors(TArray<AActor*>& OutAcceptable)
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	if (Actors.Num() == 0)
	{
		return;
	}

	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag(TagName) && !OutAcceptable.Contains(Actor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Added actor %s"), *Actor->GetName());
			OutAcceptable.Add(Actor);
		}
	}
}


// Called every frame
void UDeathBallTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetAcceptableActors(Acceptable);

	if (Acceptable.Num() >= 2 && Ball && !bIsSimulatingPhysics)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reached"));
		UPrimitiveComponent* BallComponent = Cast<UPrimitiveComponent>(Ball->GetRootComponent());
		if (BallComponent)
		{
			BallComponent->SetSimulatePhysics(true);
			bIsSimulatingPhysics = true;
		}
	}
}

void UDeathBallTriggerComponent::SetRotator(URotatorComponent* NewRotator)
{
	Rotator = NewRotator;
}

void UDeathBallTriggerComponent::SetBall(AActor* NewBall)
{
	Ball = NewBall;
}


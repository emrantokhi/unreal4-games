// Copyright Emran Tokhi 2022

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TimerManager.h"
#include "Tower.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InRange()) {
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay() 
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition() 
{
	if (InRange()) 
	{
		Fire();
	}
}

//Check to see if the tank is in range
bool ATower::InRange() 
{
	if (Tank) {
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= ActivationDistance)
		{
			return true;
		}
	}
	
	return false;
}
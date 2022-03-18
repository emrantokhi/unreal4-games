// Copyright Emran Tokhi 2022

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TimerManager.h"
#include "Tower.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank)
	{
		//Check to see if the tank is in range
		if (GetDistToTank() <= ActivationDistance)
		{
			RotateTurret(Tank->GetActorLocation());
		}
	}
}

void ATower::BeginPlay() 
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition() 
{
	if (GetDistToTank() <= ActivationDistance) 
	{
		Fire();
	}
}

float ATower::GetDistToTank() 
{
	return FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
}
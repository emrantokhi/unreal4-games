// Copyright Emran Tokhi 2022

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksGameMode.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"

AToonTanksGameMode::AToonTanksGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	//Tank may be null, but that's okay, since DeadActor won't be equal to null!
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController) {
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		if (TargetTowers == 0) 
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}


void AToonTanksGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//UActorComponent* TankHealthComponent = Tank->GetComponentByClass(HealthComponentClass);
	if (TankHealthComponent)
	{
		DisplayHUD(TankHealthComponent->GetCurrentHealth(), TankHealthComponent->GetMaxHealth(), TargetTowers);
	}
}


int32 AToonTanksGameMode::GetTargetTowerCount() 
{
	TArray<AActor*> Towers;

	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();

}


void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); //Player index 0
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	//Find and set the health component
	TArray<UActorComponent*> Components = Tank->GetComponents().Array();
	for (int i = 0; i < Components.Num(); i++) 
	{
		if (Components[i]->GetName() == TEXT("Health"))
		{
			TankHealthComponent = Cast<UHealthComponent>(Components[i]);
		}
	}
	
	StartGame();

	//Prevent input to the player tank
	if (ToonTanksPlayerController) {
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		//Start a timer
		FTimerHandle PlayerEnableTimerHandle;
		
		FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController, 
			&AToonTanksPlayerController::SetPlayerEnabledState, 
			true
		);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, InputDelegate, StartDelay, false);
	}
}
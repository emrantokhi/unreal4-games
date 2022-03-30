// Copyright Emran Tokhi 2022

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksGameMode.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"

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
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
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
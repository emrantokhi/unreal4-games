// Copyright 2022 Emran Tokhi


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	
	//This means player has died
	if (PlayerController)
	{
		EndGame(false);
	}
	else
	{		
		//Check if AI are all dead
		for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
		{
			//If there is at least 1 alive, just exit the function
			if (!Controller->IsDead())
			{
				return;
			}
		}

		//If they are all dead, call EndGame
		EndGame(true);

	}
}

void AKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		//Leave focus on self
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

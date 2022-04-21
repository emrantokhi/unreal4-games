// Copyright 2022 Emran Tokhi


#include "KillEmAllGameModeBase.h"

void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	
	//This means player has died
	if (PlayerController)
	{
		PlayerController->GameHasEnded(nullptr, false);
	}
}

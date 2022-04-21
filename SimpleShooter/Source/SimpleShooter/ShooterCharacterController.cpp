// Copyright 2022 Emran Tokhi


#include "ShooterCharacterController.h"
#include "TimerManager.h"

void AShooterCharacterController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	GetWorldTimerManager().SetTimer(RestartHandle, this, &AShooterCharacterController::RestartingLevel, RestartDelay);
}

void AShooterCharacterController::RestartingLevel()
{
	SwitchLevel(TEXT("/Game/Maps/SandboxLevel"));
}

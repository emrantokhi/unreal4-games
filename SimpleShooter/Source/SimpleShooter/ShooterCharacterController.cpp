// Copyright 2022 Emran Tokhi


#include "ShooterCharacterController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterCharacterController::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget(this, HUDClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}

void AShooterCharacterController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)
	{
		UUserWidget* WinScreenWidget = CreateWidget(this, WinScreenClass);
		
		if (WinScreenWidget)
		{
			WinScreenWidget->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreenWidget = CreateWidget(this, LoseScreenClass);

		if (LoseScreenWidget && HUDWidget)
		{
			LoseScreenWidget->AddToViewport();
			HUDWidget->RemoveFromViewport();
		}

	}
	GetWorldTimerManager().SetTimer(RestartHandle, this, &AShooterCharacterController::RestartingLevel, RestartDelay);
	
}

void AShooterCharacterController::RestartingLevel()
{
	SwitchLevel(TEXT("/Game/Maps/SandboxLevel"));
}

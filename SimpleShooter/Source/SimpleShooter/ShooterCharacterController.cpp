// Copyright 2022 Emran Tokhi


#include "ShooterCharacterController.h"
#include "ShooterAIController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"

void AShooterCharacterController::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget(this, HUDClass);
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

		if (LoseScreenWidget)
		{
			RemoveHUD();
			LoseScreenWidget->AddToViewport();
		}
	}
}

void AShooterCharacterController::RestartingLevel()
{
	SwitchLevel(TEXT("/Game/Maps/SandboxLevel"));
}

void AShooterCharacterController::ChangePause()
{
	bIsPaused = !bIsPaused;
	if (bIsPaused && PauseClass)
	{
		PauseWidget = CreateWidget(this, PauseClass);
		if (PauseWidget)
		{
			PauseWidget->AddToViewport();
		}
	}
	else if(!bIsPaused && PauseClass && PauseWidget)
	{
		PauseWidget->RemoveFromViewport();
	}
}

bool AShooterCharacterController::GetPaused() const
{
	return bIsPaused;
}

int32 AShooterCharacterController::GetNumEnemies() const
{
	AKillEmAllGameModeBase* Mode = Cast<AKillEmAllGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Mode)
	{
		return Mode->GetNumberOfEnemies();
	}
	return -1;
}

void AShooterCharacterController::AddHUD()
{
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}

void AShooterCharacterController::RemoveHUD()
{
	if (HUDWidget && HUDWidget->IsInViewport())
	{
		HUDWidget->RemoveFromViewport();
	}
}

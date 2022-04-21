// Copyright 2022 Emran Tokhi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	
	void RestartingLevel();

private:
	UPROPERTY(EditAnywhere, Category = "Restart Level")
	float RestartDelay = 5.f;

	FTimerHandle RestartHandle;
};

/** Restarts the current level */
//UFUNCTION(exec)
//virtual void RestartLevel();
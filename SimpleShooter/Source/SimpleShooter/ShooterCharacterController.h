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
	
	UFUNCTION(BlueprintCallable)
	void RestartingLevel();

	//Switches the pause variable to the opposite
	UFUNCTION(BlueprintCallable)
	void ChangePause();

	UFUNCTION(BlueprintPure)
	bool GetPaused() const;

	UFUNCTION(BlueprintPure)
	int32 GetNumEnemies() const;

	UFUNCTION(BlueprintCallable)
	void AddHUD();

protected:
	virtual void BeginPlay() override;

private:

	bool bIsPaused = false;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> PauseClass;

	class UUserWidget* HUDWidget = nullptr;

	class UUserWidget* PauseWidget = nullptr;
};
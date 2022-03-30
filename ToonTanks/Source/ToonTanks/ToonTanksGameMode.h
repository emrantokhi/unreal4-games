// Copyright Emran Tokhi 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank = nullptr;
	class AToonTanksPlayerController* ToonTanksPlayerController = nullptr;

	float StartDelay = 3.0f;

	int32 TargetTowers = 0;

	int32 GetTargetTowerCount();
	void HandleGameStart();
};

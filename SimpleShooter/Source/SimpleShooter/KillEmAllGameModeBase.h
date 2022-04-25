// Copyright 2022 Emran Tokhi

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameModeBase : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

	int32 GetNumberOfEnemies() const;

protected:
	virtual void BeginPlay() override;
	
private:
	void EndGame(bool bIsPlayerWinner);

	void HandleGameStart();

	int32 NumOfEnemies = 0;
};

// Copyright 2022 Emran Tokhi

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;

	bool IsDead() const;

private:
	APawn* PlayerPawn = nullptr;

	bool bIsDead = false;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior = nullptr;
};

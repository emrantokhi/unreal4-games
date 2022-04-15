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

private:
	APawn* PlayerPawn = nullptr;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior = nullptr;
};

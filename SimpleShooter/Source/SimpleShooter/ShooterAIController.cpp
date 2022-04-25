// Copyright 2022 Emran Tokhi


#include "ShooterAIController.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterAIController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	//DetachFromPawn();
	Destroy();
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* AIPawn = Cast<AShooterCharacter>(GetPawn());
	
	if (AIPawn)
	{
		return AIPawn->IsDead();
	}
	return true;
}
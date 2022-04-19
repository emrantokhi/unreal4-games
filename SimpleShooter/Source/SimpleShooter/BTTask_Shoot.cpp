// Copyright 2022 Emran Tokhi


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	if(!OwnerComp.GetAIOwner()) 
	{
		return EBTNodeResult::Failed;
	}

	AShooterCharacter* Pawn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	Pawn->Shoot();

	return EBTNodeResult::Succeeded;
}

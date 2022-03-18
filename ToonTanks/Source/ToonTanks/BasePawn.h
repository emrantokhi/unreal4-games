// Copyright Emran Tokhi 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:

	void SetupComponents();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing Speed", meta = (AllowPrivateAccess = "true"))
	float FiringSpeed = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combined Components", meta = (AllowPrivateAccess = "true"))
	//Forward declaration, need the include in the cpp file to reduce header file size by preprocessor
	class UCapsuleComponent* CapsuleComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combined Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combined Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combined Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawn = nullptr;

};

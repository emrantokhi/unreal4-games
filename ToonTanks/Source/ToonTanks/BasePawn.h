// Copyright Emran Tokhi 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class USoundBase;
class UParticleSystem;
class UCapsuleComponent;
class AProjectile;
class UCameraShakeBase;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:

	void SetupComponents();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing Speed", meta = (AllowPrivateAccess = "true"))
	float FiringSpeed = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combined Components", meta = (AllowPrivateAccess = "true"))
	//Forward declaration, need the include in the cpp file to reduce header file size by preprocessor
	UCapsuleComponent* CapsuleComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combined Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combined Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combined Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawn = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AProjectile> ProjectileBPClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* DeathParticles = nullptr;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* DeathSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;
};

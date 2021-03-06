// Copyright Emran Tokhi 2021


#include "BasePawn.h"
#include "Camera/CameraShakeBase.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h" 
#include "Particles/ParticleSystem.h"
#include "Projectile.h"
#include "Sound/SoundBase.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupComponents();
}

void ABasePawn::HandleDestruction() 
{
	// TODO: Handle all visual and sound effects here when pawn dies
	if (DeathParticles) 
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}

	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}

	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathCameraShakeClass);
	}
}

void ABasePawn::SetupComponents() 
{
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));

	//Set the capsule component as the root
	RootComponent = CapsuleComp;
	BaseMesh->SetupAttachment(CapsuleComp);
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawn->SetupAttachment(TurretMesh);
}

void ABasePawn::IsFiring(bool bFire)
{
	bFiring = bFire;
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	//Need to find Vector line between destination (LookAtTarget) and start point (this's location)
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();

	//Get the rotation of the vector
	FRotator TargetRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	//Set TurretMesh's rotation to the YAW only of the TargetRotation so it doesnt aim up or down
	TurretMesh->SetWorldRotation(TargetRotation);

}

void ABasePawn::Fire()
{
	//Check if the last bullet is still firing
	if (ProjectileBPClass && !bFiring) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBPClass,
			ProjectileSpawn->GetComponentLocation(),
			ProjectileSpawn->GetComponentRotation()
			);

		Projectile->SetOwner(this);
		if (bIsTank)
		{
			bFiring = true;
		}
	}
}
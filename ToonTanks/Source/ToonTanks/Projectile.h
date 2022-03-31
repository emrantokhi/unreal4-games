// Copyright Emran Tokhi 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UCameraShakeBase;
class USoundBase;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	void SetupComponents();

	UFUNCTION()
	//Callback function for the multicast delegate OnComponentHit
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* MovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	UParticleSystemComponent* SmokeTrail = nullptr;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* HitParticles = nullptr;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* LaunchSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound = nullptr;
};

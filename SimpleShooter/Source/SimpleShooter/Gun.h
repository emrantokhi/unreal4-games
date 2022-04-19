// Copyright 2022 Emran Tokhi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMesh = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleParticles = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactCharParticles = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactNonCharParticles = nullptr;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxBulletRange = 1000.f; //About 10 meters

	UPROPERTY(EditAnywhere, Category = "Combat")
	float BulletDamage = 10.f; //About 10 meters
};

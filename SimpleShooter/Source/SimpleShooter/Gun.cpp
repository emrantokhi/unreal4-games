// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));

	RootComponent = Root;
	GunMesh->SetupAttachment(RootComponent);
}

void AGun::PullTrigger()
{
	if (GunMesh && MuzzleParticles)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleParticles, GunMesh, TEXT("MuzzleFlashSocket"));
		
		//Get Player Camera's location and rotation for line trace
		FVector ViewLocation;
		FRotator ViewRotation;

		APawn* Character = Cast<APawn>(GetOwner());
		if (!Character)
		{
			return;
		}
		AController* Control = Character->GetController();
		if (!Control)
		{
			return;
		}

		Control->GetPlayerViewPoint(ViewLocation, ViewRotation);

		//Line Trace
		FHitResult HitResult;
		FVector EndPoint = ViewLocation + ViewRotation.Vector() * MaxBulletRange;
		bool bBulletHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			ViewLocation,
			EndPoint,
			ECC_GameTraceChannel1
		);
		
		//If the bullet has hit
		if (bBulletHit) {
			//Add Check if AI char and make this ImpactCharParticles
			FVector ShotDirection = -ViewRotation.Vector();
			if (ImpactNonCharParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactNonCharParticles, HitResult.Location, ShotDirection.Rotation(), true);
			}
			//TODO::else if(ImpactNonCharParticles) play that emitter

			FPointDamageEvent DamageEvent(BulletDamage, HitResult, ShotDirection, nullptr);
			if (HitResult.GetActor()) 
			{
				HitResult.GetActor()->TakeDamage(BulletDamage, DamageEvent, Control, this);
			}
		}
	}
}


// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


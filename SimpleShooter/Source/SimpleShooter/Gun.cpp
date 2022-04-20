// Copyright 2022 Emran Tokhi


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

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());

		bool bBulletHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			ViewLocation,
			EndPoint,
			ECC_GameTraceChannel1,
			Params
		);
		
		//If the bullet has hit
		if (bBulletHit) {
			FVector ShotDirection = -ViewRotation.Vector();
			//If the actor hit was a Pawn, use these particles
			if (ImpactCharParticles && Cast<APawn>(HitResult.GetActor()))
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactCharParticles, HitResult.Location, ShotDirection.Rotation(), true);
			}
			//Anything else use these
			else if (ImpactNonCharParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactNonCharParticles, HitResult.Location, ShotDirection.Rotation(), true);
			}

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


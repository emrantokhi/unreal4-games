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
		
		FVector ViewLocation;
		FRotator ViewRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

		DrawDebugCamera(GetWorld(), ViewLocation, ViewRotation, 90.f, 3.f, FColor::Red, true);
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


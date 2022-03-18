// Copyright Emran Tokhi 2021


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank() 
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerPtr) {

		FHitResult HitResult;
		PlayerControllerPtr->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult
		);
		
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 6.f, 18, FColor::Red, false, -1.f, (uint8)0U, 1.f);

		if (HitResult.Actor != this)
		{
			RotateTurret(HitResult.ImpactPoint);
		}
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerControllerPtr = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value) 
{
	FVector DeltaLocation(0.f);

	DeltaLocation.X = Value * TankSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value) {
	FRotator DeltaRotation(0.f);
	//Value passed in through UE and changed through button press
	DeltaRotation.Yaw = Value * TankRotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	//True is for Sweeping (Allows collisions)
	AddActorLocalRotation(DeltaRotation, true);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

// Copyright 2022 Emran Tokhi

#include "ShooterCharacter.h"
#include "Gun.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	if (Gun)
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Gun->SetOwner(this);
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	 
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	
	//For Controller to make sure movement is frame independent 
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);


	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("ChangeCamera"), EInputEvent::IE_Pressed, this, &AShooterCharacter::ChangeCamera);

}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(CurrentHealth, DamageToApply);
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentHealth);

	return DamageToApply;
}

bool AShooterCharacter::IsDead() const
{
	if (CurrentHealth > 0)
	{
		return false;
	}
	return true;
}

void AShooterCharacter::ChangeCamera()
{
	if (SpringArmComp)
	{
		SpringArmComp->SocketOffset = SpringArmComp->SocketOffset * -1.f;
		FVector NewLocation = SpringArmComp->GetRelativeLocation();
		NewLocation.Y = NewLocation.Y * -1.f;
		SpringArmComp->SetRelativeLocation(NewLocation);
	}
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * GetWorld()->GetDeltaSeconds() * RotationRate);
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * GetWorld()->GetDeltaSeconds() * RotationRate);
}

void AShooterCharacter::Shoot()
{
	if (Gun)
	{
		Gun->PullTrigger();
	}
}

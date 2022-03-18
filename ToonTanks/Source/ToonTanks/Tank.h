// Copyright Emran Tokhi 2021

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void Move(float Value);
	void Turn(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TankSpeed = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TankRotateSpeed = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera = nullptr;

	UPROPERTY()
	APlayerController* PlayerControllerPtr = nullptr;
};

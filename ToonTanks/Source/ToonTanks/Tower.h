// Copyright Emran Tokhi 2022

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
	
protected:

	virtual void BeginPlay() override;
	
private:
	class ATank* Tank;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float ActivationDistance = 10.f;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;
	
	FTimerHandle FireRateTimerHandle;

	void CheckFireCondition();
	bool InRange();
};

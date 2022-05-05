// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DeathBallTriggerComponent.generated.h"

class URotatorComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UDeathBallTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDeathBallTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void GetAcceptableActors(TArray<AActor*>& OutAcceptable);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetRotator(URotatorComponent* NewRotator);

	UFUNCTION(BlueprintCallable)
	void SetBall(AActor* NewBall);

private:

	UPROPERTY(EditAnywhere)
	FName TagName;

	URotatorComponent* Rotator = nullptr;

	AActor* Ball;

	TArray<AActor*> Acceptable;
	
	bool bIsSimulatingPhysics = false;
};

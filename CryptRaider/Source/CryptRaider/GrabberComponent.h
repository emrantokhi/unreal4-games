// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabberComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Released();
	
	UFUNCTION(BlueprintCallable)
	void Grab();

private:
	UPROPERTY(EditAnywhere)
	float LineTraceLength = 10.f;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 100.f;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200.f;

	class UPhysicsHandleComponent* PhysicsHandle = nullptr;

	bool GetGrabbableInReach(FHitResult& OutHit) const;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */

class UMoverComponent;
class URotatorComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMoverComponent* Mover);	
	
	UFUNCTION(BlueprintCallable)
	void AddRotator(URotatorComponent* NewRotator);

	bool HasAcceptableActor() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	FName TagName = "Unlock1";

	UPROPERTY(EditAnywhere)
	bool bIsDoubleTrigger = false;

	bool bHasAcceptableActor = false;

	UMoverComponent* MoverComponent = nullptr;

	TArray<URotatorComponent*> RotatorComponents;

	AActor* GetAcceptableActor();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DoubleTriggerComponent.generated.h"

class UMoverComponent;
class UTriggerComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UDoubleTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:

	UDoubleTriggerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMoverComponent* Mover);

	UFUNCTION(BlueprintCallable)
	void SetOtherTrigger(UTriggerComponent* Trigger);

private:
	UPROPERTY(EditAnywhere)
	FName TagName = "Unlock1";

	UMoverComponent* MoverComponent = nullptr;

	UTriggerComponent* OtherTrigger = nullptr;

	AActor* GetAcceptableActor();
};

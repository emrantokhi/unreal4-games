// Copyright Emran Tokhi 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "RatSpin.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API URatSpin : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URatSpin();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RotateMouse(float DeltaTime);
		
private:
	UPROPERTY(EditAnywhere);
	float RotateSpeed = 10.f;
};

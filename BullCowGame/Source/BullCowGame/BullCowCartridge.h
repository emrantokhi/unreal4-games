// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void IntroduceGame() const;
	void SetupGame();
	void ProcessGuess(const FString& Input);
    void LoseOrKeepLife(const FString& Input);
	bool IsIsogram(const FString& Input) const;
	void EndGame();

	// Your declarations go below!
	private:
	FString HiddenWord;
	bool bGameOver;
	int32 Lives;
};

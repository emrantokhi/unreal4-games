// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

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
	void PopulateList();
	FBullCowCount GetBullCows(const FString& Input) const;
	void GiveHint();

	private:
	TArray<FString> WordList;
	FString HiddenWord;
	bool bGameOver;
	bool bHintGiven;
	int32 Lives;
};

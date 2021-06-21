// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
	//FString Text = "";
};
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;
	TArray<FString> GetValidWords(const TArray<FString>& WordList)const;

	void GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const;// BullCount and CowCount can be out parameters, & work on original variable no const can change
	FBullCowCount GetBullCowsStruct(const FString& Guess) const;
																					
private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	TArray<FString> Isograms;
	
};

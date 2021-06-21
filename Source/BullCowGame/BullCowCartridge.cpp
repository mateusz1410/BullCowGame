// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

	/*	REF

		int32 a =0;

		int32 b = 5;

		int32& refa= a; // "refa" always have same value as "a" variable

		//change "refa" mean change "a", and change "a" mean change "refa"

		Synonim

		a= 3; //then a = 3 , refa = 3

		refa = b; // then b = 5, refa = 5, a = 5
	*/

	/*		Struct

	FBullCowCount Count = {2,3,"test"};// set Bull = 2 Cow = 3 Equals to Count.Bull = 2, Count.Cows = 3
	PrintLine(TEXT("Bull = %i, Cows = %i, Text = %s"), Count.Bulls, Count.Cows, *Count.Text);

	*/
	Isograms = GetValidWords(Words);
	SetupGame();

}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{

	if(bGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else
	{

		ProcessGuess(PlayerInput);
		
	}

}

void UBullCowCartridge::SetupGame()
{
	PrintLine(TEXT("Welcome to Bull Cows!"));

	HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num()-1)];
	Lives = HiddenWord.Len();
	bGameOver = false;

	PrintLine(TEXT("Guess the %i later word!"), HiddenWord.Len());
	PrintLine(FString::Printf(TEXT("The HiddenWorld is: %s."), *HiddenWord));

	PrintLine(TEXT("You have %i lives."),Lives);
	PrintLine(TEXT("Type in your guess and \npress enter to continue..."));


}

void UBullCowCartridge::EndGame()
{
bGameOver = true;

PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("You have WON!"));
		EndGame();
		return;
	}


	if (Guess.Len() != HiddenWord.Len())
	{
		PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);

		return;
	}

	if (!IsIsogram(Guess))
	{
		PrintLine(TEXT("No repeating letters, guess again"));
		return;
	}

	--Lives;
	PrintLine(TEXT("Lost a life!"));

	if (Lives <= 0)
	{
		ClearScreen();
		PrintLine(TEXT("You have no live left!"));
		PrintLine(TEXT("\nThe hidden word was: %s"), *HiddenWord);
		EndGame();
		return;
	}
	/* OUT Params
	
		int32 Bulls = 0, Cows = 0; // out parameters
		GetBullCows(Guess, Bulls, Cows);

		//PrintLine(TEXT("You have %i Bulls and %i Cows"), Bulls, Cows);
	*/

	FBullCowCount Score = GetBullCowsStruct(Guess);
	PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

	PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
	for (int32 Index = 0; Index < Word.Len(); Index++)
	{
		for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
		{
			if (Word[Index] == Word[Comparison])
			{
				return false;
			}

		}

	}
	return true;
	//ctrl + alt + LMB  before place to change chang many place at one 
   //shift + alt + downArrow write in many line at ones
   //PrintLine(TEXT("%c"), Word[Index]); %c character
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
	TArray<FString> ValidWords;

	for (FString WordTemp : WordList)
	{
		if (WordTemp.Len() >= 4 && WordTemp.Len() <= 8)
		{
			if (IsIsogram(WordTemp))
			{
				ValidWords.Emplace(WordTemp); // emplace == add
				//PrintLine(TEXT("%s"), *Words[Index]);
			}
		}
	}

	//for (int32 Index = 0; Index < ValidWords.Num(); Index++)
	//{
	//	PrintLine(TEXT("%s"), *ValidWords[Index]);
	//}


	return ValidWords;
}
void UBullCowCartridge::GetBullCows(const FString & Guess, int32 & BullCount, int32 & CowCount) const
{
	BullCount = 0;
	CowCount = 0;

	for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
	{
		if (Guess[GuessIndex] == HiddenWord[GuessIndex]) // this letter is in this spot in hiddenword
		{
			BullCount++;
			continue; // end this step of loop go to next one
		}
		//can use else insded of continue;
		for (int32 HiddenIndex = 0; HiddenIndex < Guess.Len(); HiddenIndex++) // this letter is in hgiddenword
		{
			if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
			{
				CowCount++;
				break; // get out from loop, find letter on other spot, and letter can be in word only one time
			}
		}
	}

}

FBullCowCount UBullCowCartridge::GetBullCowsStruct(const FString & Guess) const
{
	FBullCowCount Count;

	for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
	{
		if (Guess[GuessIndex] == HiddenWord[GuessIndex]) // this letter is in this spot in hiddenword
		{
			Count.Bulls++;
			continue; // end this step of loop go to next one
		}
		//can use else insded of continue;
		for (int32 HiddenIndex = 0; HiddenIndex < Guess.Len(); HiddenIndex++) // this letter is in hgiddenword
		{
			if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
			{
				Count.Cows++;
				break; // get out from loop, find letter on other spot, and letter can be in word only one time
			}
		}
	}

	return Count;
}

	
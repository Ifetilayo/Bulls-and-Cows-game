#pragma once
#include "FBullCow.h"
#include<map>
#define TMap std::map//to make syntax unreal friendly

BullCow::BullCow()
{ 
	Reset();
}

void BullCow::Reset()
{
	MyCurrentTry = 1;
	bGameWon = false;
	const FString HIDDEN_WORD = "bread";//must be an isogram
	Myword = HIDDEN_WORD;
}

int32 BullCow::GetMaxtries()const
{
	TMap<int32, int32>WordLengthtoMaxTries{ {3,4},{4,7}, {5,10},{6,12} };
	return WordLengthtoMaxTries[Myword.length()];
};


FString BullCow::GetIsogram()const
{
	return FString();
}

EGuessStatus BullCow::CheckGuessValidity(FString Guess)const
{
	if (!IsIsogram(Guess)) 
	{ 
		return EGuessStatus::Not_isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length()!= GetMyWordLength())
	{
		return EGuessStatus::Wrong_length;
	}
	else
		return EGuessStatus::Ok;
}

//receives a valid guess and increases turn and returns count
FBullCowCount BullCow::SubmitValidGuess(FString Guess)
{ 
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 MywordLength = Myword.length();
	//loop through all the letters in the guess
	for (int32 i = 0; i < MywordLength;i++) 
	{
		//compare letters against hidden word
		for (int32 j = 0; j < MywordLength; j++) 
		{
			//if they match then
			if (Guess[j] == Myword[i])
			{
				if(i==j)
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++; 
			}
		}
	}
	if (BullCowCount.Bulls == MywordLength)
		bGameWon = true;
	return BullCowCount;
}

int32 BullCow::GetMyWordLength() const
{
	return Myword.length();
}

bool BullCow::IsIsogram(FString Word)const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> Letterseen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		
		if (Letterseen[Letter]) { return false; }//if the letter is in the map
												//no isogram
		else{//add letter to the map
			Letterseen[Letter]= true;
		}
			
	}
	return true;
}

bool BullCow::IsLowerCase(FString Word) const
{
	if (Word.length() <= 1) { return true; }
	for (auto Letter : Word)
	{
		if (!islower(Letter)) {
			return false;
		}
		else
			return true;
	}
	
}

bool BullCow::IsGameWon()const
{
	return bGameWon;
}

int32 BullCow::GetTry()
{	
	return MyCurrentTry;
}
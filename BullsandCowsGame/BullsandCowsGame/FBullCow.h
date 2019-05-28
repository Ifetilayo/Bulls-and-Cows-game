/*The game logic(no view code or direct user interaction)
the game is a simple guess the word game based on mastermind*/

#pragma once
#include <string>'

//To make the syntax Unreal friendly
using FString=std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus 
{
	invalid,
	Ok,
	Not_isogram,
	Wrong_length,
	Not_Lowercase
};

class BullCow
{
public:
	BullCow();
	void Reset();
	int32 GetMyWordLength()const;
	int32 GetMaxtries()const;
	int32 GetTry();
	FString GetIsogram()const;
	EGuessStatus CheckGuessValidity(FString)const;
	FBullCowCount SubmitValidGuess(FString Guess);
	bool IsGameWon()const;


private:
	//initializations are in reset() which is called in the constructor
	int32 MyCurrentTry;
	FString Myword;
	bool bGameWon;
	bool IsIsogram(FString)const;
	bool IsLowerCase(FString)const;
	const FString HIDDEN_WORDS[4] = { "ant","sold","bread","planet" };
};
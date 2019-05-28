#pragma once
#include<iostream>
#include<string>
#include "FBullCow.h"

//To make syntax unreal friendly
using FText=std::string;
using int32=int;

//instantiate a new game which we re-use across plays
BullCow BCGame;

//Function prototypes
void PrintIntro(int32 Length);
FText GetValidGuess();
void PlayGame(const int32& WordLength);
bool AsktoPlayAgain();
void PrintGameSummary();

int main() 
{
	int32 WordLength = BCGame.GetMyWordLength();
	
	bool bWantsToPlayAgain = false;
	do
	{
		PlayGame(WordLength);
		bWantsToPlayAgain=AsktoPlayAgain();
	} 
	while (bWantsToPlayAgain);

	return 0;
}

void PrintIntro(int32 Length)
{
	//std::cout << "" << std::endl;
	std::cout << "	  ____        _ _                       _    _____						" << std::endl;
	std::cout << "	 |  _ \\      | | |                     | |  / ____|						" << std::endl;
	std::cout << "	 | |_) |_   _| | |___    __ _ _ __   __| | | |     _____      _____		" << std::endl;
	std::cout << "	 |  _ <| | | | | / __|  / _` | '_ \\ / _` | | |    / _ \\ \\ /\\ / / __|	" << std::endl;
	std::cout << "	 | |_) | |_| | | \\__ \\ | (_| | | | | (_| | | |___| (_) \\ \V  \V /\\__ \\	" << std::endl;
	std::cout << "	 |____/ \\__,_|_|_|___/  \\__,_|_| |_|\\__,_|  \\_____\\___/ \\_/\\_/ |___/	" << std::endl;


	std::cout << "\nCan you guess the " << Length << " letter isogram I'm thinking of? " << std::endl;
	std::cout << "\nDescription: Bulls represent the number of correct letters in the right position while " << std::endl;
	std::cout<<"             cows represent the number of correct letters in the wrong position" << std::endl;
	std::cout << "\nRiddle: I'm something you eat, The warmer I am, the fresher I am. What am I?" << std::endl;
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::invalid;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxtries() << std::endl;

		std::cout << "Enter your guess: ";

		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_length:
			std::cout << "Please enter a " << BCGame.GetMyWordLength() << " letter word \n\n" << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lowercase \n\n";
			break;
		case EGuessStatus::Not_isogram:
			std::cout << "Enter only an isogram(A word that has only one occurence of each word) \n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::Ok);
	return Guess;
}

//Plays a single game to completion
void PlayGame(const int32& WordLength)
{
	BCGame.Reset();
	int32 Maxtries = BCGame.GetMaxtries();
	
	PrintIntro(WordLength);
	 
	while(!BCGame.IsGameWon() && BCGame.GetTry()<=Maxtries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
}


void PrintGameSummary() 
{
	if (BCGame.IsGameWon() == true)
		std::cout << "Congrats You Won the Game!!!! \n" << std::endl;
	else
		std::cout << "Sorry, you didn't guess the word correctly :(\n" << std::endl;
}

bool AsktoPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText response;
	getline(std::cin, response);
	if ((response[0] == 'y') || (response[0] == 'Y'))
		return true;
	else
		return false;
}
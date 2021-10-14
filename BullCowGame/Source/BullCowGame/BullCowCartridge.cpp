// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    //Introducing the game
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the 5 letter word!\n")); //Hard coded number, Remove it
    PrintLine(TEXT("Type in a guess!"));
    PrintLine(TEXT("Press enter to continue!"));

    HiddenWord = TEXT("muted"); //Setting the hidden word
    Lives = 5; //setting amount of lives
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // Check if play again (this is a loop)
    ClearScreen();
    // Display lives
    if (Input == HiddenWord) { // == is case insensitive, .Equals is case sensitive
        PrintLine(Input + TEXT(" is the hidden word!"));
        //exit loop
    }
    else {
        PrintLine(Input + TEXT(" is not the hidden word. Try again!"));
    }

    // Check if not isogram or Check if not right number of characters
        // remove life if they are not
    // Check if keyword Quit (will not be in list of isograms)
    // Are the lives greater than 0
        // if not, show loss message and ask if play again
        // else quit the game
 
}
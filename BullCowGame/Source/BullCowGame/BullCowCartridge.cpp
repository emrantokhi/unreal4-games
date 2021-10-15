#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();

    PrintLine(TEXT("The hidden word is %s."), *HiddenWord); //Debug line
    PrintLine(TEXT("The hidden word has %i characters."), HiddenWord.Len()); //Debug line

    IntroduceGame();
}

void UBullCowCartridge::IntroduceGame() {
    //Introducing the game
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!\n"), HiddenWord.Len()); 
    PrintLine(TEXT("Type in a guess!"));
    PrintLine(TEXT("Press enter to continue!"));
}

void UBullCowCartridge::SetupGame() {
    HiddenWord = TEXT("muted"); 
    Lives = 5; 
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // Check if play again (this is a loop)
    ClearScreen();
    // Display lives
    if (Input == HiddenWord) { // == is case insensitive, .Equals is case sensitive
        PrintLine(TEXT("%s is the hidden word!"), *Input);
        //exit loop
    }
    else {
        PrintLine(TEXT("%s is not the hidden word."), *Input);
        if (Input.Len() == HiddenWord.Len()) {
            PrintLine(TEXT("%s has the correct number of letters!"), *Input);
        }
        else {
            PrintLine(TEXT("The hidden word is %i letters long, try again."), HiddenWord.Len()); //Hard coded number
        }
    }
    // Check if not isogram or Check if not right number of characters
        // remove life if they are not
    // Check if keyword Quit (will not be in list of isograms)
    // Are the lives greater than 0
        // if not, show loss message and ask if play again
        // else quit the game
}
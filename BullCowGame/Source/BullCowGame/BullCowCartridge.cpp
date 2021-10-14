#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    IntroduceGame();
    SetupGame();
}

void UBullCowCartridge::IntroduceGame() {
    //Introducing the game
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the 5 letter word!\n")); //Hard coded number, Remove it
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
        PrintLine(Input + TEXT(" is the hidden word!"));
        //exit loop
    }
    else {
        PrintLine(Input + TEXT(" is not the hidden word."));
        if (Input.Len() == HiddenWord.Len()) {
            PrintLine(Input + TEXT(" has the correct number of letters!"));
        }
        else {
            PrintLine(TEXT("The hidden word is 5 letters long, try again.")); //Hard coded number
        }
    }
    // Check if not isogram or Check if not right number of characters
        // remove life if they are not
    // Check if keyword Quit (will not be in list of isograms)
    // Are the lives greater than 0
        // if not, show loss message and ask if play again
        // else quit the game
 
}
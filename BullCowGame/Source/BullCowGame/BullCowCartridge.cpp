#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();
}

void UBullCowCartridge::IntroduceGame() {
    //Introducing the game
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!\n"), HiddenWord.Len()); 
    PrintLine(TEXT("Type in a guess!"));
    PrintLine(TEXT("Press enter to continue!\n\nEnter in 'quit' to quit!"));
    PrintLine(TEXT("\nLives: %i\n"), Lives);
}

void UBullCowCartridge::SetupGame() {
    HiddenWord = TEXT("muted"); 
    bGameOver = false;
    Lives = HiddenWord.Len(); 

    //PrintLine(TEXT("The hidden word is %s."), *HiddenWord); //Debug line
    //PrintLine(TEXT("The hidden word has %i characters."), HiddenWord.Len()); //Debug line
    IntroduceGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    
    //If the current game is over
    if (bGameOver) {
        ClearScreen();
        SetupGame();
    }
    //Continue playing the current game if it is not over
    else { 
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::ProcessGuess(const FString& Input) {

    //If the input is quit, quit the game
    if (Input.ToLower() == "quit") {
        PrintLine(TEXT("You quit the game!\n\n"));
        EndGame();
        return;
    }
    
    //If the input is correct
    else if (Input == HiddenWord) { // == is case insensitive, .Equals is case sensitive
        PrintLine(TEXT("%s is the hidden word!\n\nCongrats on winning!\n\n"), *HiddenWord);
        EndGame();
        return;
    }

    //If the Input is incorrect
    else {
        PrintLine(TEXT("%s is not the hidden word."), *Input);

        LoseOrKeepLife(Input);

        //If there are no more lives left
        if (Lives < 1) {
            EndGame();
        }
        //Else if there are lives left, print out the ability to guess again
        else {
            PrintLine(TEXT("Type in a new guess and press Enter!\n"));
        }

        return;
    }
}

void UBullCowCartridge::LoseOrKeepLife(const FString& Input) {
    bool SameLength;
    bool Isogram = IsIsogram(Input);

    //Check for similar length
    if (Input.Len() == HiddenWord.Len()) {
        PrintLine(TEXT("%s has the correct number of letters!"), *Input);
        SameLength = true;
    }
    else {
        PrintLine(TEXT("The hidden word has %i letters, try again."), HiddenWord.Len());
        SameLength = false;
    }

    //If the guessed word has the same length and is an isogram but is incorrect, lose a life
    if (SameLength && Isogram) {
        PrintLine(TEXT("\nYou have lost a life!"));
        --Lives;
    }

    PrintLine(TEXT("\nLives: %i\n"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Input) {
    //Loop, take first letter, check it with other letters
    //If there is the same, return false, otherwise keep going
    //at the end return true
    for (int i = 0; i < Input.Len(); i++) {
        for (int j = 0; j < Input.Len(); j++) {
            if (i == j) {
                continue;
            }
            else if (Input[i] == Input[j]) {
                PrintLine(TEXT("%s is not an isogram!\n"), *Input);
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Game over! Press enter to play again..."));
}
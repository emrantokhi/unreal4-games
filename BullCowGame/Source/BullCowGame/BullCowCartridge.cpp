#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    //Fill up the WordList array from a file
    PopulateList();

    SetupGame();
}

void UBullCowCartridge::PopulateList() {
    //stores the path of the list
    //FPaths::ProjectContentDir returns absolute path to Content directory
    //The / in the middle concantenates (it's overloaded) 
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordList/HiddenWordList.txt");

    //Allows list to be created at runtime instead of bloating up compile time
    FFileHelper::LoadFileToStringArray(WordList, *WordListPath);
}

void UBullCowCartridge::IntroduceGame() const {
    //Introducing the game
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!\n"), HiddenWord.Len()); 
    PrintLine(TEXT("Type in a guess!"));
    PrintLine(TEXT("Press enter to continue!\n\nEnter in 'quit' to quit!"));
    PrintLine(TEXT("\nLives: %i\n"), Lives);
}

void UBullCowCartridge::SetupGame() {
    //FMath::RandHelper returns a number between 0 and the argument-1
    //The argument is WordList.Num() which is the length of the array
    HiddenWord = WordList[FMath::RandRange(0, WordList.Num() - 1)]; 
    bGameOver = false;
    Lives = HiddenWord.Len() * 3; 

    //PrintLine(TEXT("The hidden word was %s.\n"), *HiddenWord); //Debug line
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
        PrintLine(TEXT("You quit the game!\n"));
        PrintLine(TEXT("The hidden word was %s.\n"), *HiddenWord); //Debug line
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
        PrintLine(TEXT("%s is not the hidden word."), *Input.ToLower());

        LoseOrKeepLife(Input.ToLower());

        //If there are no more lives left
        if (Lives < 1) {
            PrintLine(TEXT("The hidden word was %s.\n"), *HiddenWord); 
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
    
    //Print out bulls and cows
    int32 Bulls, Cows;
    GetBullCows(Input, Bulls, Cows);

    PrintLine(TEXT("\n%i Bulls! (Letters in the right spot)\n%i Cows! (Letters in the incorrect spot)\nLives: %i\n"), Bulls, Cows, Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Input) const {
    for (int32 i = 0; i < Input.Len(); i++) {

        for (int32 j = i + 1; j < Input.Len(); j++) {

            if ((Input[i] == Input[j])) {
                PrintLine(TEXT("%s is not an isogram!\n"), *Input);
                return false;
            }
        }
    }
    return true;
}


void UBullCowCartridge::GetBullCows(const FString& Input, int32& Bulls, int32& Cows) const {
    Bulls = 0;
    Cows = 0;

    //for every index of guess is same as index of Hidden, Bulls++
    //if not a bull, is it a cow, if yes cows++
    for (int32 Index = 0; Index < Input.Len(); Index++) {
        //If there is a bull, continue
        if ((Index < HiddenWord.Len()) && (Input[Index] == HiddenWord[Index])) {
            Bulls++;
            continue;
        }
        //If not a bull, then check if there are cows
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++) {
            if (Input[Index] == HiddenWord[HiddenIndex]) {
                Cows++;
                break;
            }
        }
        
    }
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Game over! Press enter to play again..."));
}

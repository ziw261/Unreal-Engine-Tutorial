#include <iostream>
#include <ctime>

void PrintIntroduction(int Difficulty){
    std::cout << "You are a secret agent breaking into a secure server room " << Difficulty << std::endl;
    std::cout << "Enter the correct code to continue...\n\n";
}


bool PlayGame(int Difficulty){

    PrintIntroduction(Difficulty);

    int Num_A = rand() % Difficulty + Difficulty , Num_B = rand() % Difficulty + Difficulty, Num_C = rand() % Difficulty + Difficulty;
    int Sum = Num_A + Num_B + Num_C;
    int Product = Num_A * Num_B * Num_C;

    std::cout << "+ There are 3 numbers in the code\n";
    std::cout << "+ The codes add-up to: " << Sum << std::endl;
    std::cout << "+ The codes multiply to give: " << Product << std::endl;

    int GuessA, GuessB, GuessC;
    std::cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    if(GuessSum == Sum && GuessProduct == Product){
        std::cout << "You win!\n";
        return true;
    } else {
        std::cout << "Bruh...\n";
        return false;
    }

}


int main(){

    srand(time(NULL));  // create new random sequence
    int LevelDifficulty = 1;
    int const MaxDifficulty = 5;

    bool bLevelComplete = false;;
    while (LevelDifficulty <= MaxDifficulty){
        bLevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear();
        std::cin.ignore();

        if (bLevelComplete){
            LevelDifficulty++;
        }
    }

    std::cout << "Yeah Yeah, u win u win \n";
    return 0;
}
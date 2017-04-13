#include <iostream> //cin, cout, endl
#include <vector>   //vector
#include <ctime>    //time
#include <cstdlib>  //srand

class Number
{
public:
    int randomNumber;
    std::vector<int> guesses;
    int difficulty;
    int currentGuess;
    int maxGuesses;

    //srand (time(NULL));

    //sets the number of guesses the user will have to get the number
    void setDifficulty(int setDifficulty)
    {
        difficulty = setDifficulty;

        switch (difficulty)
        {
            //Easy
            case 1:
            {
                maxGuesses = 7;
                std::cout << "You've chosen Easy mode. That means you will have " << maxGuesses << " guesses. Good Luck!";
                break;
            }
            //Medium
            case 2:
            {
                maxGuesses = 5;
                std::cout << "You've chosen Medium mode. That means you will have " << maxGuesses << " guesses. Good Luck!";
                break;
            }
            //Hard
            case 3:
            {
                maxGuesses = 3;
                std::cout << "You've chosen Hard mode. That means you will have " << maxGuesses << " guesses. Good Luck!";
                break;
            }
            //Cobra Bubbles
            default:
            {
                std::cout << "Something has indeed gone very wrong... \n";
                break;
            }
        }
    }

    void guessNumber()
    {
            std::cout << "Which number would you like to guess? Please guess any number from 1 to 100. \n";
            std::cin >> currentGuess;

            while (currentGuess < 1 || currentGuess > 100)
            {
                std::cout << "You have entered an invalid number. Please guess again. \n";
            }

            std::cout << "You have guessed " << currentGuess << std::endl;
            guesses.push_back(currentGuess);
    }

    void highLowCheck(int currentGuess, int actual, int guessTotal, int maxGuesses)
    {
        if (currentGuess == actual)
        {
            std::cout << "Congratulations! You've found the correct number in " << guessTotal << " guesses!";
        }

        else
        {
            if (currentGuess != actual && guessTotal == maxGuesses)
            {
                std::cout << "Unfortunately, you've guessed incorrectly and you've run out of guesses. The actual number was " << actual << ".\n";
                std::cout << "Better luck next time.\n";
            }

            else if (currentGuess > actual)
            {
                std::cout << "You've guessed too high! Please try again. Guess any number from 1 - 100. (But higher than your last one) \n";
                ++guessTotal;
                guessNumber();

            }
            else if (currentGuess < actual)
            {
                std::cout << "You've guessed too low! Please try again. Guess any number from 1 - 100. (But lower than your last one) \n";

            }
        }
    }
};


int main() {
    Number one;

    std::cout << "Welcome to the Number Guesser. Please select a difficulty. Enter 1 for Easy, 2 for Medium, 3 for Hard. \n";
    std::cin >> one.difficulty;
    //std::cout << "You've chosen " << one.difficulty << ".\n";

    while(one.difficulty != 1 && one.difficulty != 2 && one.difficulty !=3)
    {
        //std::cin.clear()
        std::cout << "You have entered an invalid response. Please try again. Enter 1 for Easy, 2 for Medium, 3 for Hard. \n";
        std::cin >> one.difficulty;
        //std::cout << "You've chosen " << one.difficulty << ".\n";
    }
    one.setDifficulty(one.difficulty);



    return 0;
}
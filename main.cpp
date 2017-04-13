#include <iostream> //cin, cout, endl
#include <vector>   //vector
#include <ctime>    //time
#include <cstdlib>  //srand

class Number
{
public:
    std::vector<int> guesses;
    int difficulty;
    int currentGuess;
    int maxGuesses;
    int actual;


    int setActual()
    {
        srand (time(NULL));
        actual = rand() % 100;

        if (actual == 0)
        {
            ++actual;
        }

        std::cout << actual << std::endl;
    }

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
                std::cout << "You've chosen Easy mode. That means you will have " << maxGuesses << " guesses. Good Luck!\n";
                break;
            }
            //Medium
            case 2:
            {
                maxGuesses = 5;
                std::cout << "You've chosen Medium mode. That means you will have " << maxGuesses << " guesses. Good Luck!\n";
                break;
            }
            //Hard
            case 3:
            {
                maxGuesses = 3;
                std::cout << "You've chosen Hard mode. That means you will have " << maxGuesses << " guesses. Good Luck!\n";
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

    bool guessNumber()
    {
        currentGuess = 0;
        std::cout << "Which number would you like to guess? Please guess any number from 1 to 100. \n";
        std::cin >> currentGuess;

        if (currentGuess < 1 || currentGuess > 100)
        {
            std::cout << "You have entered an invalid number. Please guess again. \n";
            return false;
        }

        std::cout << "You have guessed " << currentGuess << std::endl;
        guesses.push_back(currentGuess);
        return true;
    }

    void highLowCheck(int guess, int actual, int guessTotal, int maxGuesses)
    {
        if (guess == actual)
        {
            std::cout << "Congratulations! You've found the correct number in " << guessTotal << " guesses!";
        }

        else
        {
            if (guess != actual && guessTotal == maxGuesses)
            {
                std::cout << "Unfortunately, you've guessed incorrectly and you've run out of guesses. The actual number was " << actual << ".\n";
                std::cout << "Better luck next time.\n";
            }

            else if (guess > actual)
            {
                std::cout << "You've guessed too high! Please try again. Guess any number from 1 - 100. (But lower than your last one) \n";
                ++guessTotal;
                while(!guessNumber());
                highLowCheck(currentGuess, actual, guessTotal, maxGuesses);
            }
            else if (guess < actual)
            {
                std::cout << "You've guessed too low! Please try again. Guess any number from 1 - 100. (But higher than your last one) \n";
                ++guessTotal;
                while(!guessNumber());
                highLowCheck(currentGuess, actual, guessTotal, maxGuesses);
            }
        }
    }

    void outputGuesses()
    {
        std::cout << "The numbers you guessed are below." << std::endl;
        for (int x = 0; x < guesses.size(); x++)
        {
            std::cout << guesses[x] << std::endl;
        }
    }
};


int main() {
    Number one;

    std::cout << "Welcome to the Number Guesser. Please select a difficulty. Enter 1 for Easy, 2 for Medium, 3 for Hard. \n";
    std::cin >> one.difficulty;

    while(one.difficulty != 1 && one.difficulty != 2 && one.difficulty !=3)
    {
        std::cout << "You have entered an invalid response. Please try again. Enter 1 for Easy, 2 for Medium, 3 for Hard. \n";
        std::cin >> one.difficulty;
    }
    one.setDifficulty(one.difficulty);
    one.setActual();
    while(!one.guessNumber());
    one.highLowCheck(one.currentGuess, one.actual, 1, one.maxGuesses);
    one.outputGuesses();

    return 0;
}
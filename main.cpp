#include <iostream> //cin, cout, endl
#include <vector>   //vector

class UserGuess
{
public:
    std::vector<int> guesses;
    std::vector<std::string> whichWay;
    int difficulty;
    int currentGuess;
    int maxGuesses;
    int actual;


    void setActual()
    {
        srand( static_cast<unsigned int>(time(NULL)));
        actual = rand() % 100;

        if (actual == 0)
        {
            ++actual;
        }

        //std::cout << actual << std::endl;
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
                std::cout << "You've chosen Easy mode. This means you will have " << maxGuesses << " guesses. Good Luck!\n";
                break;
            }
            //Medium
            case 2:
            {
                maxGuesses = 5;
                std::cout << "You've chosen Medium mode. This means you will have " << maxGuesses << " guesses. Good Luck!\n";
                break;
            }
            //Hard
            case 3:
            {
                maxGuesses = 3;
                std::cout << "You've chosen Hard mode. This means you will have " << maxGuesses << " guesses. Good Luck!\n";
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

        std::cout << "You have guessed " << currentGuess << ".\n";
        guesses.push_back(currentGuess);
        return true;
    }

    void highLowCheck(int guess, int actual, int guessTotal, int maxGuesses)
    {
        if (guess == actual)
        {
            whichWay.push_back("just right.");
            std::cout << "Congratulations! You've found the correct number in " << guessTotal << " guesses!\n";
        }

        else
        {
            if (guess != actual && guessTotal == maxGuesses)
            {
                std::cout << "Unfortunately, you've guessed incorrectly and you've run out of guesses.\n\n The actual number was " << actual << ".\n";
                if (guess < actual)
                {
                    std::cout << "Your final guess was too low.\n";
                    whichWay.push_back("too low.");
                }
                else if (guess > actual)
                {
                    std::cout << "Your final guess was too high.\n";
                    whichWay.push_back("too high.");
                }

                std::cout << "Better luck next time.\n";
            }

            else if (guess > actual)
            {
                whichWay.push_back("too high.");
                std::cout << "You've guessed too high! Please guess again. (But lower than your last guess) \n";
                std::cout << "You have " << maxGuesses - guessTotal << " guesses remaining.\n" << std::endl;
                ++guessTotal;
                while(!guessNumber());
                highLowCheck(currentGuess, actual, guessTotal, maxGuesses);
            }
            else if (guess < actual)
            {
                whichWay.push_back("too low.");
                std::cout << "You've guessed too low! Please guess again. (But higher than your last guess)\n";
                std::cout << "You have " << maxGuesses - guessTotal << " guesses remaining.\n" << std::endl;
                ++guessTotal;
                while(!guessNumber());
                highLowCheck(currentGuess, actual, guessTotal, maxGuesses);
            }
        }
    }

    void outputGuesses()
    {
        std::cout << "\nThe numbers you guessed are below:" << std::endl;
        for (int x = 0; x < guesses.size(); x++)
        {
            std::cout << "You guessed ";
            std::cout << guesses[x] << " which was ";
            std::cout << whichWay[x] << std::endl;

        }
    }

};

class ComputerGuess
{
    int commonNumbers[];
    int guess;
    int difficulty;
    int maxGuesses;

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
                std::cout << "You've chosen Easy mode. This means the computer will have " << maxGuesses << " guesses.\n";
                break;
            }
            //Medium
            case 2:
            {
                maxGuesses = 5;
                std::cout << "You've chosen Medium mode. This means the computer will have " << maxGuesses << " guesses.!\n";
                break;
            }
            //Hard
            case 3:
            {
                maxGuesses = 3;
                std::cout << "You've chosen Hard mode. This means the computer will have " << maxGuesses << " guesses.\n";
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

    bool guesser(int low, int high, int guessTotal)
    {

    }
};


int main() {
    UserGuess one;

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
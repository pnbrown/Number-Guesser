#include <iostream> //cin, cout, endl
#include <iomanip>  //setfill, setw
#include <vector>   //vector
#include <fstream>  //ifstream, ofstream

class UserGuess
{
public:
    std::vector<int> guesses;
    std::vector<std::string> whichWay;
    int difficulty;
    int currentGuess;
    int maxGuesses;
    int actual;
    
    //This is our function that will chose a random number for our user to try and guess
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
    
    //True or false method that takes the users guess and checks to make sure it a number that is between 1 and 100
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
    
    //This method is checks to see if the user's guess is correct
    void highLowCheck(int guess, int actual, int guessTotal, int maxGuesses)
    {
        if (guess == actual)
        {
            whichWay.push_back("just right.");
            std::cout << "Congratulations! You've found the correct number in " << guessTotal << " guesses!\n";
        }
        
        else
        {
            //This is to stop the program once you run out of your guesses and have not chosen the correct number.
            if (guess != actual && guessTotal == maxGuesses)
            {
                std::cout << "Unfortunately, you've guessed incorrectly and you've run out of guesses.\n\nThe actual number was " << actual << ".\n";
                
                //if the guess is less than the actual or more than the actual on the final guess, we have an if statement to take care of that.
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
            
            //This is the else if ladder that will keep track of the guesses remaining as we continue to try and guess the chosen number.
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
    
    //At the end of your game, the program will output all the numbers that you guessed.
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
public:
    int guess;
    int guessTotal;
    int possibilities[100] = {};
    int total = 0;
    int left = 0;
    int right = 100;
    
    void learn()
    {
        int addOne = 0;
        int index;
        std::ifstream myfile;
        myfile.open("results.csv");
        
        while(myfile >> index)
        {
            //std::cout << index << std::endl;
            addOne = index - 1;
            ++possibilities[addOne];
            ++total;
        }
        
        int amount = 0;
        for (int x = 0; x < 100; ++x)
        {
            amount = amount + possibilities[x];
        }
        
        
        /*
         //For Testing
         std::cout << amount << std::endl;
         
         
         std::cout << total << std::endl;
         
         for (int x = 0; x < 100; ++x)
         {
         std::cout << possibilities[x] << std::endl;
         }
         
         std::cout << total << std::endl;
         */
        
    }
    
    void setGuess(int total, int low, int high)
    {
        int x = 0;
        while (x  < total/2)
        {
            x = x + possibilities[low];
            ++low;
        }
        guess = low + 1;
    }
    
    void guesser(int guessTotal)
    {
        bool validAnswer = false;
        char answer;
        while(!validAnswer)
        {
            std::cout << "Is your number " << guess << "? If yes, enter Y, if no, enter N." << std::endl;
            std::cin >> answer;
            
            if ((answer == 'y' || answer == 'Y' || answer == 'n' || answer == 'N'))
            {
                validAnswer = true;
            }
            else
            {
                std::cout << "You have entered an invalid response. Please try again. " << std::endl;
                validAnswer = false;
            }
        }
        
        if ((answer == 'y' || answer == 'Y'))
        {
            std::cout << "Thank you for playing!" << std::endl;
        }
        
        else if (answer == 'n' || answer == 'N')
        {
            validAnswer = false;
            std::cout << "Is your number higher or lower? Enter h for higher or l for lower. " << std::endl;
            std::cin >> answer;
            while(!validAnswer)
            {
                if ((answer == 'h' || answer == 'H' || answer == 'l' || answer == 'L'))
                {
                    validAnswer = true;
                }
                else
                {
                    std::cout << "You have entered an invalid response. Please try again" << std::endl;
                }
            }
        }
        
        if (answer == 'l' || answer == 'L')
        {
            right = guess - 1;
            total = total/2;
            setGuess(total, left, right);
            guesser(guessTotal);
        }
        else if (answer == 'h' || answer == 'H')
        {
            left  = guess - 1;
            total = total/2;
            setGuess(total, left, right);
            guesser(guessTotal);
        }
    }
    
    void update()
    {
        std::cout << "Would you like to help improve our program by entering your number? Please enter y for yes and n for no" << std::endl;
        
        char update;
        std::cin >> update;
        
        if (update == 'n' || update == 'N')
        {
            std::cout << "Thank you for playing." << std::endl;
            return;
        }
        
        else
        {
            std::cout << "Which number did you choose?" << std::endl;
            std::ofstream myfile;
            myfile.open("results.csv", std::ios::app);
            std::cout << "Please enter your number" << std::endl;
            int number;
            std::cin >> number;
            myfile << std::endl << number;
        }
    }
    
    
};


int main() {
    bool menuRepeat = true;
    while (menuRepeat)
    {
        int choice;
        
        std::cout << std::setfill('*') << std::setw(40) << "*" << std::endl;
        std::cout << std::setfill(' ') << std::setw(39) << std::left << "* Main Menu:" << std::right << "*\n";
        std::cout << std::setfill(' ') << std::setw(39) << std::left << "* Enter # to run program or Quit" << std::right << "*\n";
        std::cout << std::setfill(' ') << std::setw(39) << std::left << "* 1) You Guess Computers Number" << std::right << "*\n";
        std::cout << std::setfill(' ') << std::setw(39) << std::left << "* 2) I Guess Your Number" << std::right << "*\n";
        std::cout << std::setfill(' ') << std::setw(39) << std::left << "* 3) Quit" << std::right << "*\n";
        std::cout << std::setfill('*') << std::setw(40) << "*" << std::endl;
        
        std::cin >> choice;
        
        switch(choice)
        {
            case 1:
            {
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
                break;
            }
            case 2:
            {
                ComputerGuess one;
                one.learn();
                one.setGuess(one.total, one.left, one.right);
                one.guesser(one.guessTotal);
                one.update();
                break;
            }
            case 3:
            {
                std::cout << "Thank you for playing. Goodbye." << std::endl;
                menuRepeat = false;
                break;
                
            }
            default:
            {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "You have entered an invalid response. Please try again.";
            }
                
        }
    }
    return 0;
}

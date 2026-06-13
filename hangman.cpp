#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

// changeCase declaration for UI use
string changeCase(string str, string strCase);

class UI {
    private:
        string hangmanStatus[7] = 
        {
            R"(    _____
    |   |
        |
        |
        |
________|)",
            R"(    _____
    |   |
    O   |
        |
        |
________|)",
            R"(    _____
    |   |
    O   |
    |   |
        |
________|)",
            R"(    _____
    |   |
    O   |
   /|   |
        |
________|)",
            R"(    _____
    |   |
    O   |
   /|\  |
        |
________|)",
            R"(    _____
    |   |
    O   |
   /|\  |
   /    |
________|)",
            R"(    _____
    |   |
    O   |
   /|\  |
   / \  |
________|)",
        };
    public:
        /**
         * @brief Shows the hangman game's status, wrong guesses, and current problem.
         * 
         * @param problem An array holding the problem's letters, blanks, spaces, and hyphens.
         * @param pLength The problem array's length.
         * @param livesLost The number of wrong answers.
         * @param wrongLetters An array holding each wrong answer the user has made.
         */
        void showInfo(const char problem[], int pLength, int livesLost, const char wrongLetters[]) {
            // Print the hangman status depending on
            // wrong guesses. More wrong guesses = more stickman limbs
            cout << "\n\n" << hangmanStatus[livesLost] << "\n\n";
            
            // If there are no wrong letters, don't print wrong answers.
            // Otherwise, loop through the array and
            // print each wrong answer according to lives lost
            if (wrongLetters[0] != ' ') {
                cout << "Wrong Guesses: ";
                for (int i = 0; i <= livesLost - 1; i++) {
                    if (i == livesLost - 1) {
                        cout << wrongLetters[i] << "\n";
                    } else {
                        cout << wrongLetters[i] << ", ";
                    }
                }
            }

            // Loop through the problem array and
            // print each letter along with a space
            // (or new line if it's the last letter)
            cout << "Problem: ";
            for (int i = 0; i <= pLength - 1; i++) {
                if (i == pLength - 1) {
                    cout << problem[i] << "\n";
                } else {
                    cout << problem[i] << " ";
                }
            }
        }
        
        /**
         * @brief Gets the user's guess from user input.
         * 
         * @return The user's guess.
         */
        char guessLetter() {
            // Declarations
            char guess;
            string guessString;
            bool validGuess = false;
            
            // As long as the guess is not valid, get user input
            cout << "Guess a letter: ";
            while (!validGuess) {
                getline(cin, guessString);

                // The guess is only valid if it's a single letter.
                // This also turns the guess uppercase for consistency
                if (guessString.length() == 1 && isalpha(guessString[0])) {
                    guess = toupper(guessString[0]);
                    validGuess = true;
                } else {
                    cout << "Input must be a single letter. Guess again: ";
                }
            }
            
            return guess;
        }
        
        /**
         * @brief Gets the new word from user input.
         * 
         * @return The user's word.
         */
        string inputWord() {
            string word;
            
            cout << "\nAdd a word here! It can be anything, " <<
            "as long as it only has letters, spaces, and hyphens (-).";
            cout << "\nIf you want to go back to the menu, enter \"back to menu\".";
            cout << "\nEnter the word you want saved: ";
            getline(cin, word);

            return word;
        }

        /**
         * @brief Tells the user whether the word has been saved to file.
         * 
         * @param hasSaved A boolean telling the method whether the word saved.
         * @param word The word itself.
         */
        void confirmSave(bool hasSaved, string word) {
            switch (hasSaved)
            {
            case true:
                cout << "\nSuccessfully saved " << word << ". ";
                break;
            case false:
                cout << "\n" << word << " not saved. Did you use ONLY letters, spaces, and hyphens?\n";
                break;
            }
        }
};

class Hangman {
    private:
        UI ui;
        vector<string> wordsList = {};
        string word;
    public:
        char* problem;
        int livesLost = 0;
        char wrongLetters[6] = {' ', ' ', ' ', ' ', ' ', ' '};

        /**
         * @brief Creates a Hangman object and loads the words from file.
         */
        Hangman() {
            string line;
            ifstream wordFile("wordslist.csv");

            // Split the line from the file by commas
            // and add each word to the words list
            if (getline(wordFile, line)) {
                istringstream ss(line);
                string token;
                
                while (getline(ss, token, ',')) {
                    if (wordIsValid(token)) {
                        wordsList.push_back(token);
                    }
                }
            }

            wordFile.close();
        }

        /**
         * @brief Runs the Hangman game.
         * 
         * Creates a new problem if there are words in the word list
         * and loops through showing the game status and getting/validating
         * user guesses. The game ends if the hangman is fully drawn or
         * the whole word is guessed correctly.
         * 
         * @return A boolean telling the program whether to ask for a replay.
         */
        bool runGame() {
            // If there are no words, tell the user and
            // stop the game, skipping the replay confirmation
            if (wordsList.empty()) {
                cout << "\nNo words to play with!\n";
                return false;
            }

            // Reassigning values to default state
            livesLost = 0;
            for (int i = 0; i < 6; i++) {
                wrongLetters[i] = ' ';
            }
            
            // Randomly select an index from the words list
            // and assign to word
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, wordsList.size() - 1);
            word = wordsList.at(distr(gen));
            // word = wordsList.at(5); // Use this for testing

            // Define problem array using word length
            problem = new char[word.length()];

            // Fill out problem array with blanks/spaces/hyphens
            for (int i = 0; i < word.length(); i++) {
                if (word[i] == ' ' || word[i] == '-') {
                    problem[i] = word[i];
                } else {
                    problem[i] = '_';
                }
            }

            // Loop through gameplay until lives are lost
            // or problem is solved
            while (livesLost < 6 && !problemSolved()) {
                ui.showInfo(problem, word.length(), livesLost, wrongLetters);
                char guess = ui.guessLetter();
                checkLetter(guess);
            }
            
            // Tell the user whether they won or lost
            // (Could probably be a UI method)
            ui.showInfo(problem, word.length(), livesLost, wrongLetters);
            if (livesLost >= 6) {
                cout << "You ran out of guesses. ";
            } else if (problemSolved()) {
                cout << "You win! ";
            }

            // Delete the problem and return true for replay confirmation
            delete[] problem;
            return true;
        }
        
        /**
         * @brief Checks whether the user's guess is in the current word.
         * 
         * @param letter The letter the user guessed.
         */
        void checkLetter(char letter) {
            // Define whether the word has the letter and
            // check whether the letter has already been guessed
            bool hasLetter = false;
            bool alreadyGuessed = find(begin(wrongLetters), end(wrongLetters), letter) != end(wrongLetters);
            
            // If the letter is in the word, change the
            // according problem blanks to that letter
            for (int i = 0; i <= word.length() - 1; i++) {
                if (letter == word[i]) {
                    problem[i] = letter;
                    hasLetter = true;
                }
            }

            // If the letter is not in the word and has not
            // already been guessed, add the letter to the
            // wrong letters list and increase lives lost
            if (!hasLetter && !alreadyGuessed) {
                wrongLetters[livesLost] = letter;
                livesLost++;
            }
        }

        /**
         * @brief Validates the word and adds it to the words file if valid.
         * 
         * @return A boolean telling the program whether to ask for another word.
         */
        bool addWord() {
            // Call inputWord, assign to word, and make
            // the word uppercase for consistency
            string word = ui.inputWord();
            word = changeCase(word, "upper");

            // If the user input "back to menu", stop the
            // method and tell the program not to ask for another word
            if (word == "BACK TO MENU") {
                return false;
            }

            // Check whether the word contains only
            // letters, spaces, and hyphens
            bool isValid = wordIsValid(word);

            // Check whether the words file is empty
            ifstream checkFile("wordslist.csv");
            bool fileIsEmpty = (checkFile.peek() == fstream::traits_type::eof());
            checkFile.close();
            
            // Open word file to insert word
            ofstream wordFile("wordslist.csv", ios::app);
            
            // If the word is valid, append the word to the file.
            // If the file isn't empty, add a comma before the word
            // for use in the Hangman constructor
            if (isValid) {
                if (!fileIsEmpty) {
                    wordFile << ',';
                }
                wordFile << word;
                wordsList.push_back(word);
            }
            
            // Tell the user whether the word saved and let
            // the program ask for another word
            ui.confirmSave(isValid, word);
            wordFile.close();
            return true;
        }

        /**
         * @brief Checks whether the problem is solved.
         * 
         * Loops through each letter in the problem to see if
         * the problem matches the word. If a letter is blank,
         * return false. Otherwise, return true.
         * 
         * @return Whether or not the problem has been solved.
         */
        bool problemSolved() {
            for (int i = 0; i < word.length(); i++) {
                if (problem[i] != word[i]) {
                    return false;
                }
            }

            return true;
        }

        /**
         * @brief Checks whether a string is a valid word.
         * 
         * Loops through the word and checks whether each letter is
         * a letter, a space, or a hyphen. If a letter is not any of
         * these, return false.
         * 
         * @return Whether or not the word is valid.
         */
        bool wordIsValid(string word) {
            for (char c : word) {
                if (!isalpha(c) && c != ' ' && c != '-') {
                    return false;
                }
            }

            return true;
        }
};

/**
 * @brief Changes a string's case to uppercase or lowercase.
 * 
 * Loops through each letter of a string and changes it to
 * uppercase or lowercase, depending on the argument.
 * 
 * @param str The string to change case.
 * @param strCase The case to change the string to (upper/lower).
 * @return The modified string.
 */
string changeCase(string str, string strCase) {
    if (strCase == "lower") {
        for_each(str.begin(), str.end(), [](char& c) {
            c = tolower(c);
        });
    } else if (strCase == "upper") {
        for_each(str.begin(), str.end(), [](char& c) {
            c = toupper(c);
        });
    } else {
        cout << "String cannot change to \"" << strCase << "\". Must be \"upper\" or \"lower\".";
    }
    
    return str;
}

/**
 * @brief Creates a new Hangman object and acts as the main menu.
 * 
 * Acts as a "main menu" for the program, giving the user options
 * to play the game, add a word, or exit the program.
 * 
 * @returns 0.
 */
int main()
{
    // Make new Hangman object, declare choice
    Hangman* hangman = new Hangman();
    string choice;

    // Loops through the main menu until the user inputs "exit"
    while (choice != "exit") {
        cout << "Play | Add Word | Exit\n";
        cout << "What would you like to do? ";
        getline(cin, choice);
        choice = changeCase(choice, "lower");
        
        // Declare confirmation and loop sustainment
        // for game replays/adding more words
        string confirm = "yes";
        bool sustainLoop = true;

        if (choice == "play") {
            // Loops through playing the game until
            // user says "no" or word list is empty
            while (confirm != "no") {
                if (confirm == "yes") {
                    sustainLoop = hangman->runGame();
                    
                    if (!sustainLoop) {
                        break;
                    }
                    
                    cout << "Want to play again (yes | no)? ";
                } else {
                    cout << "You're silly. Yes or No? ";
                }

                getline(cin, confirm);
                confirm = changeCase(confirm, "lower");
            }

            cout << "\n";
        } else if (choice == "add word") {
            // Loops through adding words until the
            // user inputs "no" during the confirmation
            // or "back to menu" during the adding process
            while (confirm != "no") {
                if (confirm == "yes") {
                    sustainLoop = hangman->addWord();
                    
                    if (!sustainLoop) {
                        break;
                    }
                    
                    cout << "Want to add another word (yes | no)? ";
                } else {
                    cout << "You're silly. Yes or No? ";
                }

                getline(cin, confirm);
                confirm = changeCase(confirm, "lower");
            }

            cout << "\n";
        } else if (choice == "exit") {
            cout << "\nThanks for playing!\n";
        } else {
            cout << "\nPlease choose between the options below.\n";
        }
    }
    
    delete hangman;
    return 0;
}
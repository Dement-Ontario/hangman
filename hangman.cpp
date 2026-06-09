#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

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
        void showInfo(const char problem[], int pLength, int livesLost, const char wrongLetters[]) {
            cout << "\n\n" << hangmanStatus[livesLost] << "\n\n";
            
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

            cout << "Problem: ";
            for (int i = 0; i <= pLength - 1; i++) {
                if (i == pLength - 1) {
                    cout << problem[i] << "\n";
                } else {
                    cout << problem[i] << " ";
                }
            }
        }

        char guessLetter() {
            char guess;
            string guessString;
            
            cout << "Guess a letter: ";
            while (guessString.length() != 1 || guessString == " ") {
                cin >> guessString;

                if (guessString.length() == 1) {
                    guess = toupper(guessString[0]);
                } else {
                    cout << "\nInput too long. Guess a LETTER: ";
                }
            }
            
            return guess;
        }
};

class Hangman {
    private:
        UI ui;
        string wordsList[6] = {
            "PICKLE",
            "WYRMWOOD",
            "ALABASTER",
            "A NEWT",
            "THE VERY MODEL OF A MODERN MAJOR GENERAL",
            "PORTAL_LOVER_253"
        };
        string word;
    public:
        char* problem;
        int livesLost = 0;
        char wrongLetters[6] = {' ', ' ', ' ', ' ', ' ', ' '};

        Hangman() {
            int wordsListLength = sizeof(wordsList) / sizeof(wordsList[0]);
            
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, wordsListLength - 1);
            word = wordsList[distr(gen)];
            // word = wordsList[0]; // Use this for testing

            problem = new char[word.length()];

            for (int i = 0; i < word.length(); i++) {
                if (word[i] != ' ') {
                    problem[i] = '_';
                } else {
                    problem[i] = ' ';
                }
            }
        }

        void runGame() {
            while (livesLost < 6 && !problemSolved()) {
                ui.showInfo(problem, word.length(), livesLost, wrongLetters);
                char guess = ui.guessLetter();
                checkLetter(guess);
            }
            
            ui.showInfo(problem, word.length(), livesLost, wrongLetters);
            if (livesLost >= 6) {
                cout << "You ran out of guesses. You lose!";
            } else if (problemSolved()) {
                cout << "You got all the letters right. You win!";
            }

            delete[] problem;
        }

        void checkLetter(char letter) {
            bool hasLetter = false;
            bool alreadyGuessed = find(begin(wrongLetters), end(wrongLetters), letter) != end(wrongLetters);
            
            for (int i = 0; i <= word.length() - 1; i++) {
                if (letter == word[i]) {
                    problem[i] = letter;
                    hasLetter = true;
                }
            }

            if (!hasLetter && !alreadyGuessed) {
                wrongLetters[livesLost] = letter;
                livesLost++;
            }
        }
        
        bool problemSolved() {
            for (int i = 0; i < word.length(); i++) {
                if (problem[i] != word[i]) {
                    return false;
                }
            }

            return true;
        }
};

int main()
{
    Hangman* hangman = new Hangman();
    hangman->runGame();
    
    delete hangman;
    return 0;
}
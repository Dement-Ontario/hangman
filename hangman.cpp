#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <sstream>

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
                getline(cin, guessString);

                if (guessString.length() == 1) {
                    guess = toupper(guessString[0]);
                } else {
                    cout << "Input too long. Guess a LETTER: ";
                }
            }
            
            return guess;
        }

        string inputWord() {
            // TODO: Implement inputWord
        }

        void confirmSave(bool hasSaved) {
            // TODO: Implement confirmSave
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

        Hangman() {
            string line;
            ifstream wordFile("wordslist.csv");

            if (getline(wordFile, line)) {
                istringstream ss(line);
                string token;
                
                while (getline(ss, token, ',')) {
                    if (wordIsValid(token)) {
                        wordsList.push_back(token);
                    }
                }
            }
        }

        void runGame() {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, wordsList.size() - 1);
            word = wordsList.at(distr(gen));
            // word = wordsList.at(0); // Use this for testing

            problem = new char[word.length()];

            for (int i = 0; i < word.length(); i++) {
                if (word[i] != ' ') {
                    problem[i] = '_';
                } else {
                    problem[i] = ' ';
                }
            }

            while (livesLost < 6 && !problemSolved()) {
                ui.showInfo(problem, word.length(), livesLost, wrongLetters);
                char guess = ui.guessLetter();
                checkLetter(guess);
            }
            
            ui.showInfo(problem, word.length(), livesLost, wrongLetters);
            if (livesLost >= 6) {
                cout << "You ran out of guesses. ";
            } else if (problemSolved()) {
                cout << "You win! ";
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

        void addWord() {
            // TODO: Create addWord
        }
        
        bool problemSolved() {
            for (int i = 0; i < word.length(); i++) {
                if (problem[i] != word[i]) {
                    return false;
                }
            }

            return true;
        }

        bool wordIsValid(string word) {
            for (char c : word) {
                if (!isalpha(c) && c != ' ') {
                    return false;
                }
            }

            return true;
        }
};

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

int main()
{
    Hangman* hangman = new Hangman();
    string choice;
    while (choice != "exit") {
        cout << "Play | Add Word | Exit\n";
        cout << "What would you like to do? ";
        getline(cin, choice);
        choice = changeCase(choice, "lower");

        if (choice == "play") {
            string confirm = "yes";

            while (confirm != "no") {
                if (confirm == "yes") {
                    hangman->runGame();
                    cout << "Want to play again (yes | no)? ";
                } else {
                    cout << "You're silly. Yes or No? ";
                }

                getline(cin, confirm);
                confirm = changeCase(confirm, "lower");
            }

            cout << "\n";
        } else if (choice == "add word") {
            cout << "\nAdding words has not been implemented yet. Sorry!\n";
        } else if (choice == "exit") {
            cout << "\nHave a good day!\n";
        } else {
            cout << "\nPlease choose between the options below.\n";
        }
    }
    
    delete hangman;
    return 0;
}
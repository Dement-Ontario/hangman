#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

class UI {
    private:
        string hangmanStatus[7] = 
        {
            "None",
            "Head",
            "Body",
            "Left Arm",
            "Right Arm",
            "Left Leg",
            "Right Leg"
        };
    public:
        void showInfo(const char problem[], int livesLost, const char wrongLetters[]) {
            cout << "ShowInfo not implemented.\n";
        }

        void guessLetter() {
            cout << "guessLetter not implemented.\n";
        }
};

class Hangman {
    private:
        UI ui;
        string wordsList[4] = {"pickle", "wyrmwood", "alabaster", "a newt"};
        string word;
    public:
        char* problem;
        int livesLost = 0;
        char wrongLetters[6];

        Hangman() {
            int wordsListLength = sizeof(wordsList) / sizeof(wordsList[0]);
            
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, wordsListLength - 1);
            word = wordsList[distr(gen)];

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
                ui.showInfo(problem, livesLost, wrongLetters);
                ui.guessLetter();
                livesLost++; // Remove this!
            }

            if (livesLost >= 6) {
                cout << "\nRan out of guesses. You lose!";
            } else if (problemSolved()) {
                cout << "\nYou guess the whole word. You win!";
            }

            delete[] problem;
        }

        void checkLetter(char letter) {
            
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
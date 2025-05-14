#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#define RED "\033[31m"
#define GREEN   "\033[32m"
#define DEFAULT "\033[0m"
using namespace std;

class Hangman {
private:
    string secretWord;
    string guessedWord;
    int lives;
    bool hintProvided;

public:
    Hangman(const string& word);
    void guessLetter(char letter);
    bool isGameWon() const;
    bool isGameLost() const;
    void showGameStatus() const;
    string getSecretWord() const;
    void provideHint();
    void displayHangman(int attemptsLeft) const;
    int getLives() const { return lives; }
};

class HangmanUI {
private:
    Hangman& game;

public:
    HangmanUI(Hangman& g) : game(g) {}

    void run();
};

Hangman::Hangman(const string& word) : secretWord(word), guessedWord(word.length(), '_'), lives(6), hintProvided(false) {}

void Hangman::guessLetter(char letter) {
    bool correctGuess = false;

    for (size_t i = 0; i < secretWord.length(); ++i) {
        if (secretWord[i] == letter) {
            guessedWord[i] = letter;
            correctGuess = true;
        }
    }

    if (!correctGuess) {
        --lives;
    }
}

bool Hangman::isGameWon() const {
    return guessedWord == secretWord;
}

bool Hangman::isGameLost() const {
    return lives <= 0;
}

void Hangman::showGameStatus() const {
    cout << "Secret word: " << guessedWord << '\n';
    cout << "Lives: " << lives << '\n';
}

string Hangman::getSecretWord() const {
    return secretWord;
}

void Hangman::provideHint() {
    if (lives == 4 && !hintProvided) {
        size_t index = guessedWord.find('_');
        if (index != string::npos) {
            char hintLetter = secretWord[index];
            for (size_t i = 0; i < secretWord.length(); ++i) {
                if (secretWord[i] == hintLetter) {
                    guessedWord[i] = hintLetter;
                }
            }
            cout << "You are close to losing, here is a hint: " << endl;
            hintProvided = true;
        }
    }
}

void Hangman::displayHangman(int attemptsLeft) const {

    if (attemptsLeft == 6) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    }
    else if (attemptsLeft == 5) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    }
    else if (attemptsLeft == 4) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |     |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    }
    else if (attemptsLeft == 3) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |    /|" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    }
    else if (attemptsLeft == 2) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |    /|\\" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    }
    else if (attemptsLeft == 1) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |    /|\\" << endl;
        cout << "  |    /" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    }
    else if (attemptsLeft == 0) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |    /|\\" << endl;
        cout << "  |    / \\" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    }
}

void HangmanUI::run() {
    string input;
    cout << GREEN << "Every word in this game is a fruit." << DEFAULT << '\n';

    while (true) {
        game.showGameStatus();

        if (game.isGameLost()) {
            game.displayHangman(0); // Display hangman for attemptsLeft == 0
            cout << RED << "You've lost. The secret word was: " << game.getSecretWord() << '\n' << DEFAULT;
            break;
        }

        game.displayHangman(game.getLives());

        cout << "Enter your guess: ";
        cin >> input;

        if (input.length() == 1) {
            game.guessLetter(input[0]);
            game.provideHint();

            if (game.isGameWon()) {
                cout << GREEN << "Congratulations! You've won!\n" << DEFAULT;
                cout << GREEN << "The secret word was: " << game.getSecretWord() << '\n' << DEFAULT;
                break;
            }
        }
    }
}


int main() {
    srand(time(0));
    string words[] = { "apple", "banana", "cherry", "orange", "pear", "strawberry", "berry", "blueberry", "mango", "pineapple", "melon", "grapes", "kiwi" };

    int numWords = sizeof(words) / sizeof(words[0]);

    int randomIndex = rand() % numWords;

    Hangman game(words[randomIndex]);

    HangmanUI ui(game);

    ui.run();

    return 0;
}
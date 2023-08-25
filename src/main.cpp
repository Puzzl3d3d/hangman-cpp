#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max_wrong_guesses = 8;

char livesCharacter = '*';
char wrongCharacter = '~';
char hiddenCharacter = '?';

int display(int *wrong_guesses, string secret, vector<char> *guessed_letters) {
    string output;
    output.insert(0, max_wrong_guesses-*wrong_guesses, livesCharacter);
    if (*wrong_guesses < max_wrong_guesses) {
        output.insert(0, max_wrong_guesses - output.size(), wrongCharacter);
    }
    cout << output << endl << endl;

    int correctLetters = 0;
    for (int i = 0; i < secret.length(); i++)
    {
        char thisChar = secret[i];
        if (count(guessed_letters->begin(), guessed_letters->end(), thisChar)) {
            cout << thisChar;
            correctLetters++;
        } else {
            cout << hiddenCharacter;
        }
    }

    cout << endl;

    return correctLetters >= secret.length();
}
int doGuess(char guess, vector<char> *guessed_letters, int *wrong_guesses, string secret) {
    if (count(guessed_letters->begin(), guessed_letters->end(), guess) == 0) {
        if (secret.find(guess) != string::npos) {
            string::difference_type numInString = count(secret.begin(), secret.end(), guess);
            cout << "Letter " << guess << " appears " << numInString << " time(s) in string." << endl;
        } else {
            cout << "Letter " << guess << " not in word." << endl;
            *wrong_guesses = *wrong_guesses + 1;
        }
    } else {
        cout << "Already guessed letter " << guess << endl;
    }

    guessed_letters->push_back(guess);

    cout << endl;

    int didWin = display(wrong_guesses, secret, guessed_letters);

    if (didWin) {
        cout << endl << "Win! The word is " << secret << endl;
        return 1;
    }

    if (*wrong_guesses >= max_wrong_guesses) {
        cout << endl << "Lose! The word was " << secret << endl;
        return 1;
    }

    return 0;
}

int main() {
    cout << "Input secret word: ";
    string secret;
    getline(cin, secret);
    cout << endl;

    vector<char> guessed_letters = {};
    int wrong_guesses = 0;

    cout << endl;
    display(&wrong_guesses, secret, &guessed_letters);

    while (true) {
        cout << endl << "Enter guess: ";
        string guessS;
        getline(cin, guessS);
        
        for (int i = 0; i < guessS.length(); i++) {
            char guess = guessS[i];

            if (doGuess(guess, &guessed_letters, &wrong_guesses, secret) == 1) {
                break;
            }
        }
    }

    return main();
}
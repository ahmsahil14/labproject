#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player {
    string name;
    int age;
    string password;
    int matchesPlayed;
    int matchesWon;
    int matchesLost;
};

bool signUp(Player& player) {
    cout << "Sign Up\n";
    cout << "Name: ";
    cin >> player.name;
    cout << "Age: ";
    cin >> player.age;
    cout << "Password: ";
    cin >> player.password;

    // Initialize match statistics
    player.matchesPlayed = 0;
    player.matchesWon = 0;
    player.matchesLost = 0;

    cout << "Sign up successful!\n\n";
    return true;
}

bool signIn(const Player& player) {
    string enteredName, enteredPassword;

    cout << "Sign In\n";
    cout << "Name: ";
    cin >> enteredName;
    cout << "Password: ";
    cin >> enteredPassword;

    return (enteredName == player.name && enteredPassword == player.password);
}

void displayPlayerProfile(const Player& player) {
    cout << "\nPlayer Profile:\n";
    cout << "Name: " << player.name << endl;
    cout << "Age: " << player.age << endl;
    cout << "Matches Played: " << player.matchesPlayed << endl;
    cout << "Matches Won: " << player.matchesWon << endl;
    cout << "Matches Lost: " << player.matchesLost << endl;
}

void updatePlayerProfile(Player& player, bool isWin) {
    player.matchesPlayed++;
    if (isWin) {
        player.matchesWon++;
    } else {
        player.matchesLost++;
    }
}

void playerProfileOption(const Player& player) {
    displayPlayerProfile(player);
    cout << "\nOptions:\n";
    cout << "1. Start a new game\n";
    cout << "2. Player Profile\n";
    cout << "3. Exit\n";
    cout << "Option: ";
}

bool isLetterInWord(char letter, const string& word, string& guessedWord) {
    bool letterFound = false;
    for (size_t i = 0; i < word.length(); ++i) {
        if (tolower(word[i]) == tolower(letter)) {
            guessedWord[i] = word[i];
            letterFound = true;
        }
    }
    return letterFound;
}

void goHomeOption() {
    cout << "\nOptions:\n";
    cout << "1. Start a new game\n";
    cout << "2. Go Home\n";
    cout << "Option: ";
}

int main() {
    Player player;

    if (!signUp(player)) {
        cout << "Sign up failed. Exiting.\n";
        return 0;
    }

    char signInOption;
    cout << "Do you want to sign in? (Y/N): ";
    cin >> signInOption;

    if (signInOption == 'Y' || signInOption == 'y') {
        if (!signIn(player)) {
            cout << "Sign in failed. Exiting.\n";
            return 0;
        }
        cout << "Sign in successful!\n";
    }

    char option;

    do {
        playerProfileOption(player);
        cin >> option;

        if (option == '1') {
            // Game logic
            string words[] = {"hangman", "programming", "cplusplus", "developer", "coding",
                              "algorithm", "variable", "function", "iteration", "interface",
                              "database", "structure", "pointer", "template", "compiler",
                              "keyboard", "mouse", "monitor", "hardware", "software",
                              "keyboard", "password", "network", "internet", "security",
                              "library", "algorithm", "application", "debugging", "version",
                              "authentication", "encryption", "authentication", "optimization", "framework",
                              "parameter", "syntax", "semicolon", "statement", "declaration",
                              "expression", "inheritance", "polymorphism", "encapsulation", "abstraction",
                              "variable", "conditional", "iteration", "recursion", "assembler"};

            string clues[] = {"Word related to the game we're playing", "The act of writing code", "A programming language", "One who writes code", "Creating software",
                              "A step-by-step procedure for solving a problem", "A storage location identified by a memory address", "A reusable piece of code", "Repeating a set of instructions", "A point of interaction",
                              "A structured set of data", "The arrangement of and relations between the parts or elements of something complex", "A variable that stores the memory address of another variable", "A blueprint for creating objects", "A program that translates source code into machine code",
                              "Input device for typing characters", "Input device for pointing and clicking", "Output device for displaying information", "Physical components of a computer", "Programs and data that operate on the computer",
                              "Input device for typing characters", "Secret word for authentication", "A system of interconnected computers", "A global network of computers", "Protection against unauthorized access",
                              "A collection of books or other sources of information", "A step-by-step procedure for solving a problem", "A specific software designed for a particular purpose", "Finding and fixing errors in code", "A version of a program",
                              "Verifying the identity of a user", "Converting data into a code to prevent unauthorized access", "Verifying the identity of a user", "Making a program run more efficiently", "A pre-built structure for developing software",
                              "A variable that stores data", "Conditional statement in programming", "Repeated execution of a set of statements", "A function calling itself", "An interface for interaction between objects",
                              "A variable that can have different types", "Making decisions in programming", "Repeating a set of instructions", "A process calling itself","A low-level programming language"};


            srand(static_cast<unsigned int>(time(0)));

            int maxAttempts = 6;
            char playOption;

            do {
                int index = rand() % (sizeof(words) / sizeof(words[0]));
                string selectedWord = words[index];
                string wordClue = clues[index];

                string guessedWord(selectedWord.length(), '_');

                int attempts = 0;
                char guess;

                cout << "Clue: " << wordClue << " (Length: " << selectedWord.length() << " letters)\n";
                cout << "Welcome to Hangman!\n";

                do {
                    cout << "Word: " << guessedWord << endl;
                    cout << "Guess a letter: ";
                    cin >> guess;

                    if (isLetterInWord(guess, selectedWord, guessedWord)) {
                        cout << "Correct guess!\n";
                    } else {
                        cout << "Incorrect guess. Attempts left: " << maxAttempts - attempts << "\n";
                        ++attempts;
                    }

                    if (guessedWord == selectedWord) {
                        cout << "Congratulations! You guessed the word: " << selectedWord << "\n";
                        updatePlayerProfile(player, true);
                        break;
                    }

                } while (attempts < maxAttempts);

                if (attempts == maxAttempts) {
                    cout << "Sorry, you ran out of attempts. The word was: " << selectedWord << "\n";
                    updatePlayerProfile(player, false);
                }

                goHomeOption();
                cin >> playOption;

            } while (playOption == '1');

        } else if (option == '2') {
            displayPlayerProfile(player);
        } else if (option == '3') {
            cout << "Thank you for playing Hangman! Goodbye!\n";
            return 0;
        } else {
            cout << "Invalid option. Please choose again.\n";
        }

    } while (option != '3');

    return 0;
}

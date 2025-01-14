#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 50
#define MAX_TRIES 6

typedef struct {
    char word[MAX_WORD_LENGTH];
    char hint[MAX_WORD_LENGTH];
} WordWithHint;

WordWithHint wordList[] = {
    { "raven", "A black bird often associated with omens" },
    { "meadow", "A grassy field filled with flowers" },
    { "scroll", "A rolled piece of parchment containing text" },
    { "tome", "An ancient book filled with knowledge" }
};

void displayWord(const char word[], const bool guessed[]) {
    printf("Word: ");
    for (int i = 0; word[i] != '\0'; i++) {
        if (guessed[word[i] - 'a']) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

void drawHangman(int tries) {
    const char *hangmanParts[] = {
        "     _________",
        "    |         |",
        "    |         O",
        "    |        /|\\",
        "    |        / \\",
        "    |"
    };

    printf("\n");
    for (int i = 0; i <= tries; i++) {
        printf("%s\n", hangmanParts[i]);
    }
}

int main(void) {
    srand(time(NULL));

    int wordIndex = rand() % (sizeof(wordList) / sizeof(wordList[0]));
    const char *secretWord = wordList[wordIndex].word;
    const char *hint = wordList[wordIndex].hint;
    int wordLength = strlen(secretWord);

    char guessedWord[MAX_WORD_LENGTH] = { 0 };
    bool guessedLetters[26] = { false };

    int tries = 0;

    printf("Welcome to Hangman!\n");
    printf("Hint: %s\n", hint);

    // Main game loop
    while (tries < MAX_TRIES) {
        printf("\n");
        displayWord(secretWord, guessedLetters);
        drawHangman(tries);

        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (guessedLetters[guess - 'a']) {
            printf("You've already guessed that letter. Try again!\n");
            continue;
        }

        guessedLetters[guess - 'a'] = true;

        bool found = false;
        for (int i = 0; i < wordLength; i++) {
            if (secretWord[i] == guess) {
                found = true;
                guessedWord[i] = guess;
            }
        }

        if (found) {
            printf("Good guess!\n");
        } else {
            printf("Sorry... The letter '%c' is not in the word.\n", guess);
            tries++;
        }

        if (strcmp(secretWord, guessedWord) == 0) {
            printf("Congratulations! You've guessed the word: %s\n", secretWord);
            break;
        }
    }

    if (tries >= MAX_TRIES) {
        printf("Sorry! You've run out of tries! The word was: %s\n", secretWord);
    }

    return 0;
}

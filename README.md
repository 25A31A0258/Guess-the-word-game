#include <stdio.h>
#include <string.h>

int main() {
    char word[] = "COMPUTER";   // Secret word
    char guess[20];
    char ch;
    int i, length, attempts = 6;
    int correct = 0, found;

    length = strlen(word);

    // Initialize guessed word with underscores
    for (i = 0; i < length; i++) {
        guess[i] = '_';
    }
    guess[length] = '\0';

    printf("---- GUESS THE WORD GAME ----\n");

    while (attempts > 0 && correct < length) {
        printf("\nWord: %s", guess);
        printf("\nAttempts left: %d", attempts);
        printf("\nEnter a letter: ");
        scanf(" %c", &ch);

        found = 0;

        for (i = 0; i < length; i++) {
            if (word[i] == ch && guess[i] == '_') {
                guess[i] = ch;
                correct++;
                found = 1;
            }
        }

        if (found)
            printf("Correct guess!\n");
        else {
            printf("Wrong guess!\n");
            attempts--;
        }
    }

    if (correct == length)
        printf("\nCongratulations! You guessed the word: %s\n", word);
    else
        printf("\nGame Over! The word was: %s\n", word);

    return 0;
}

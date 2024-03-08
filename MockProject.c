#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_PLAYERS 10

typedef struct {
    char playerName[50];
    int randomNumber;
    double probability;
} Player;

int generateRandomNumber() {
    srand(time(NULL));
    return rand() % 9000 + 1000;
}

double calculateProbability(int attempts) {
    double probability = 100.0 / (1 << (attempts - 1));
    return probability;
}

void displayResults(Player players[], int numPlayers) {
    printf("\nList of results:\n");
    printf("No.\tPlayer's Name\tGuessed Number\tProbability\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("%d\t%s\t\t%d\t\t%.2f%%\n", i + 1, players[i].playerName, players[i].randomNumber, players[i].probability);
    }
}

bool isInteger(char input[]) {
    char *endptr;
    strtol(input, &endptr, 10);
    if (*endptr != '\0' || endptr == input) {
        return false;
    }
    return true;
}

int main() {
    Player players[MAX_PLAYERS];
    int numPlayers = 0;
    int choice;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Start playing\n");
        printf("2. Display list of results\n");
        printf("3. End the game\n");
        printf("Enter your choice: ");

        char input[50];
        scanf("%s", input);

        if (!isInteger(input)) {
            printf("Invalid input. Please enter again.\n");
            while (getchar() != '\n');
            continue;
        }

        choice = atoi(input);

        switch (choice) {
            case 1: {
                if (numPlayers >= MAX_PLAYERS) {
                    printf("The maximum number of players has been reached.\n");
                    break;
                }

                Player currentPlayer;
                printf("Enter your name: ");
                scanf("%s", currentPlayer.playerName);

                currentPlayer.randomNumber = generateRandomNumber();
                printf("The machine has generated a 4-digit number: %d\n", currentPlayer.randomNumber);

                int guess;
                int correctDigits = 0;
                int attempts = 0;

                while (correctDigits != 4) {
                    printf("Enter your 4-digit guess: ");
                    scanf("%d", &guess);

                    correctDigits = 0;
                    int tempRandomNumber = currentPlayer.randomNumber;
                    int guessedDigits[4] = {0};

                    for (int i = 3; i >= 0; i--) {
                        int digitGuess = guess % 10;
                        guess /= 10;

                        int digitRandom = tempRandomNumber % 10;
                        tempRandomNumber /= 10;

                        if (digitGuess == digitRandom) {
                            guessedDigits[i] = digitGuess;
                            correctDigits++;
                        }
                    }

                    for (int i = 0; i < 4; i++) {
                        if (guessedDigits[i] != 0) {
                            printf("%d", guessedDigits[i]);
                        } else {
                            printf("-");
                        }
                    }
                    printf("\n");

                    attempts++;
                }

                currentPlayer.probability = calculateProbability(attempts);
                players[numPlayers] = currentPlayer;
                numPlayers++;
                break;
            }
            case 2:
                displayResults(players, numPlayers);
                break;
            case 3:
                printf("The program has ended.\n");
                break;
            default:
                printf("Invalid choice. Please select again.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}

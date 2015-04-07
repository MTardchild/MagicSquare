#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "main.h"

int main()
{
    int MagicSquareSize = 0;
    int *MagicSquareSizePointer = &MagicSquareSize;

    printf("Please enter size of square: ");
    scanf("%d", MagicSquareSizePointer);

	int **MagicSquare = InitializeMagicSquare(MagicSquareSize);
	int NumberSum = CalculateNumberSum(MagicSquareSize);

    DrawMagicSquare(MagicSquare, MagicSquareSize);
    CheckMagicSquare(MagicSquare, MagicSquareSize, NumberSum);

    return 0;
}

void CheckMagicSquare(int **magicSquare, int magicSquareSize, int numberSum) {
	// Counter Variables
	int i = 0;
	int j = 0;
	int k = 0;

	// Saved Results
	int Horizontal = 0;
	int Vertical = 0;
	int Diagonal = 0;
	int ConDiagonal = 0;

	for (i = 0; i < magicSquareSize; i++) {
		for (j = 0; j < magicSquareSize; j++) {
			// Check hor
			if (((Horizontal += magicSquare[i][j]) != numberSum) && j == magicSquareSize-1) {
				printf("No magic happening...");
				return;
			}

			// Check vert
			if (((Vertical += magicSquare[j][i]) != numberSum) && j == magicSquareSize-1) {
				printf("No magic happening...");
				return;
			}

			if (k < magicSquareSize) {
                // Check diag
				if (((Diagonal += magicSquare[k][j]) != numberSum) && j == magicSquareSize-1) {
					printf("No magic happening...");
					return;
                }

                // Check condiag
                if (((ConDiagonal += magicSquare[magicSquareSize-1-k][magicSquareSize-1-j]) != numberSum) && j == magicSquareSize-1) {
					printf("No magic happening...");
					return;
				}
				k++;
			}

			// Reset
			if (j == magicSquareSize-1) {
				Horizontal = 0;
				Vertical = 0;
				Diagonal = 0;
				ConDiagonal = 0;
				k = magicSquareSize;
			}
		}
	}
	printf("Magic!");
}

// Calculates the value the sum should have
int CalculateNumberSum (int size) {
    int NumberCount = size*size;
    int NumberSum = 0;
    int i;

    for (i = 0; i < NumberCount; i++) {
        NumberSum += NumberCount-i;
    }
    return (NumberSum/size);
}

// Builds the Square
int **InitializeMagicSquare(int size) {
    int **MagicSquare = (int **)malloc(size*sizeof(int *));
    int *UsedNumbers = (int *)malloc(size*sizeof(int));
    int i, j;

    for (i = 0; i < size; i++) {
        MagicSquare[i] = (int *)malloc(size * sizeof(int));
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            int RandomTemp = GetRandomNumber(size);
            while (IsRandomNumberUsed(UsedNumbers, RandomTemp, size*size)) {
                RandomTemp = GetRandomNumber(size);
            }
            MagicSquare[i][j] = RandomTemp;
            UsedNumbers[i+j] = MagicSquare[i][j];
        }
    }
    return MagicSquare;
}

// Draws the MagicSquare
void DrawMagicSquare(int **magicSquare, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf(". ");
            printf("%d", magicSquare[i][j]);
            printf(" .");
        }
        printf("\n");
    }
    return;
}

// Generates random number
int GetRandomNumber(int size) {
    time_t TimeStore;
    time(&TimeStore);
    srand((unsigned int)TimeStore);

    return (rand()%(size*size))+1;
}

// Returns true if the generated randomNumber is already used
bool IsRandomNumberUsed(int *usedNumbers, int randomNumber, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        if (usedNumbers[i] == randomNumber) {
            return true;
        }
    }
    return false;
}

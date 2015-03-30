#include <stdio.h>
#include <stdlib.h>

int main()
{
	int MagicSquare[3][3] = {{2,9,4},
							 {7,5,3},
							 {6,1,8}};

	int size = sizeof(MagicSquare[0])/sizeof(int);

	// Counter Variables
	int i = 0;
	int j = 0;
	int k = 0;

	// Saved Results
	int Horizontal = 0;
	int Vertical = 0;
	int Diagonal = 0;
	int ConDiagonal = 0;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			// Check hor
			if (((Horizontal += MagicSquare[i][j]) != 15) && j == size-1) {
				printf("No magic happening...");
				return 1;
			}

			// Check vert
			if (((Vertical += MagicSquare[j][i]) != 15) && j == size-1) {
				printf("No magic happening...");
				return 1;
			}

			if (k < size) {
				// Check diag
				if (((Diagonal += MagicSquare[k][j]) != 15) && j == size-1) {
					printf("%d", Diagonal);
					printf("No magic happening...D");
					return 1;
			}

			// Check condiag
			if (((ConDiagonal += MagicSquare[3-k][3-j]) != 15) && j == size-1) {
					printf("No magic happening...CD");
					return 1;
				}
				k++;
			}

			// Reset
			if (j == size-1) {
				Horizontal = 0;
				Vertical = 0;
				Diagonal = 0;
				ConDiagonal = 0;
				k = size;
			}
		}
	}
	printf("Magic!");
	return 0;
}


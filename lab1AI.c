#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printMatrix(int array[]);
int checkRow(int array[], int row);
int checkColumn(int array[], int col);
int checkDiagonal(int array[]);

int main() {
    char a[9];
    int inta[9];
    int computingScores[9];
    int i, rowCounter, colCounter, diagCounter;

    printf("Enter input data: \n");
    for (i = 0; i < 9; i++) {
        scanf("%s", &a[i]);
    }

    printf("Tictactoe vector [");
    for (i = 0; i < 9; i++) {
        if (a[i] == 'X') {
            a[i] = '1';
        } else if (a[i] == 'O') {
            a[i] = '2';
        }
        printf(" %c", a[i]);
    }
    printf("]\n");

    for (i = 0; i < 9; i++) {
        inta[i] = a[i] - '0';
    }

    int count1 = 0, count2 = 0, count0 = 0;
    for (int j = 0; j < 9; j++) {
        if (inta[j] == 1) {
            count1++;
        } else if (inta[j] == 2) {
            count2++;
        } else {
            count0++;
        }
    }

    if (abs(count1 - count2) <= 1) {
        printf("Valid!\n");
    } else {
        printf("Invalid!!\n");
        exit(0);
    }

    double index = 0;
    for (int j = 0; j < 9; j++) {
        index += (inta[j] * pow(3, 8 - j));
    }
    printf("Index is: %.0f\n", index);

    printf("Possible Moves = \n");
    if (count1 <= count2) {
        printf("Predicting for X turn\n");
        rowCounter = 0;
        colCounter = 0;
        diagCounter = 0;

        for (i = 0; i < 9; i++) {
            if (inta[i] == 0) {
                int copyInta[9];
                for (int k = 0; k < 9; k++) {
                    copyInta[k] = inta[k];
                }
                copyInta[i] = 1;
                printMatrix(copyInta);

                for (int j = 0; j < 3; j++) {
                    if (checkRow(copyInta, j)) {
                        rowCounter++;
                    }
                }

                for (int j = 0; j < 3; j++) {
                    if (checkColumn(copyInta, j)) {
                        colCounter++;
                    }
                }

                if (checkDiagonal(copyInta)) {
                    diagCounter++;
                }

                computingScores[i] = rowCounter + colCounter + diagCounter;
            }
        }
    } else {
        printf("Predicting O turn\n");
        for (i = 0; i < 9; i++) {
            if (inta[i] == 0) {
                int copyInta[9];
                for (int k = 0; k < 9; k++) {
                    copyInta[k] = inta[k];
                }
                copyInta[i] = 2;
                printMatrix(copyInta);
                rowCounter = 0;
                colCounter = 0;
                diagCounter = 0;

                for (int j = 0; j < 3; j++) {
                    if (checkRow(copyInta, j))
                        rowCounter++;
                }

                for (int j = 0; j < 3; j++) {
                    if (checkColumn(copyInta, j))
                        colCounter++;
                }

                if (checkDiagonal(copyInta)) {
                    diagCounter++;
                }

                computingScores[i] = rowCounter + colCounter + diagCounter;
            }
        }
    }

    return 0;
}

void printMatrix(int array[]) {
    for (int i = 0; i < 9; i++) {
        if (array[i] == 1)
            printf("X ");
        else if (array[i] == 2)
            printf("O ");
        else
            printf("0 ");
        if ((i + 1) % 3 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

int checkRow(int array[], int row) {
    int start = row * 3;
    int value = array[start];
    if (value == 0)
        return 0;
    for (int i = start + 1; i < start + 3; i++) {
        if (array[i] != value)
            return 0;
    }
    return 1;
}

int checkColumn(int array[], int col) {
    int start = col;
    int value = array[start];
    if (value == 0)
        return 0;
    for (int i = start + 3; i < start + 7; i += 3) {
        if (array[i] != value)
            return 0;
    }
    return 1;
}

int checkDiagonal(int array[]) {
    if ((array[0] != 0 && array[0] == array[4] && array[0] == array[8]) ||
        (array[2] != 0 && array[2] == array[4] && array[2] == array[6]))
        return 1;
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    char a[9]; // Array for X's and O's
    int inta[9]; // Array for 1's and 2's
    int i;

    printf("Enter input data: \n");
    for (i = 0; i < 9; i++) {
        scanf("%s", &a[i]);
    }

    // Printing the Tic Tac Toe Vector
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

    // Converting "1" and "2" into 1 and 2 {parse method}
    for (i = 0; i < 9; i++) {
        inta[i] = a[i] - '0';
    }

    // Checking for validity
    int count1 = 0, count2 = 0;
    for (int j = 0; j < 9; j++) {
        if (inta[j] == 1) {
            count1++;
        } else if (inta[j] == 2) {
            count2++;
        }
    }

    if (abs(count1 - count2) == 1) {
        printf("Valid!\n");
    } else {
        printf("Invalid!!\n");
        exit(0);
    }

    // Calculating Index in Rule Base
    // {Unique Scoring System For each board position}
    double index = 0;
    for (int j = 0; j < 9; j++) {
        index += (inta[j] * pow(3, 8 - j));
    }
    printf("Index is: %.0f\n", index);

    return 0;
}

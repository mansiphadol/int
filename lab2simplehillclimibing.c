#include <stdio.h>
#include <math.h>

#define N 3

int goal[N][N];
int arr[4][2];
int temp[N][N];
int mov;
float ans = 100;

float evaluate(int goal[N][N], int current[N][N]) {
    int dist = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist += pow(goal[i][j] - current[i][j], 2);
        }
    }
    float hval = (float)sqrt(dist);
    dist = 0;
    return hval;
}

void drawMatrix(int current[N][N], int x, int y, int p, int q) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == x && j == y) {
            	//x and y : Coordinates in the current matrix where a value is being moved.
                temp[i][j] = current[p][q];
            } else if (i == p && j == q) {
                temp[i][j] = 0;
            } else {
                temp[i][j] = current[i][j];
            }
        }
    }
}
//to check the neighbouring indices 
//The function checks four directions (up, down, right, left) from the given position (i, j) 
//and populates the arr array with valid neighboring indices.
int findIndex(int i, int j, int arr[4][2]) {
    int k = 0, cnt = 0;
    
    //The given condition checks for the neighboring index in the upward direction
    if ((N > (i - 1) && i - 1 >= 0) && (N > j && j >= 0)) {
        arr[k][0] = i - 1;
        arr[k][1] = j;
        k++;
        cnt++;
    }
    //downward neighbouring indices 
    if (N > i + 1 && i + 1 >= 0 && N > j && j >= 0) {
        arr[k][0] = i + 1;
        arr[k][1] = j;
        k++;
        cnt++;
    }
    //rightward direction 
    if ((N > i && i >= 0) && (N > (j + 1) && j + 1 >= 0)) {
        arr[k][0] = i;
        arr[k][1] = j + 1;
        k++;
        cnt++;
    }
    //leftward direction
    if ((N > i && i >= 0) && (N > j - 1 && j - 1 >= 0)) {
        arr[k][0] = i;
        arr[k][1] = j - 1;
        k++;
        cnt++;
    }
    mov = cnt;
    return mov;
}

int main() {
    printf("Enter goal board state: ");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &goal[i][j]);
        }
    }

    printf("Enter initial board state: ");
    int current[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &current[i][j]);
        }
    }

    ans = evaluate(goal, current);
    printf("Initial Hvalue: %.2f\n", ans);

    if (ans == 0) {
        printf("Initial state is the goal state.\n");
    } else {
    	// to determine the next available move or the first empty position in a game board.
        int x = -1, y = -1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (current[i][j] == 0) {
                    x = i;
                    y = j;
                }
            }
        }

        mov = findIndex(x, y, arr);
        float bestHval = ans;
        int betterState[N][N];
        for (int i = 0; i < mov; i++) {
            drawMatrix(current, x, y, arr[i][0], arr[i][1]);
            float tans = evaluate(goal, temp);
            if (tans < bestHval) {
                bestHval = tans;
                for (int p = 0; p < N; p++) {
                    for (int q = 0; q < N; q++) {
                        betterState[p][q] = temp[p][q];
                    }
                }
                break;
            }
        }
        if (bestHval >= ans) {
            printf("No operator left\n");
        } else {
            for (int p = 0; p < N; p++) {
                for (int q = 0; q < N; q++) {
                    current[p][q] = betterState[p][q];
                }
            }
            ans = bestHval;
            printf("Current Hvalue: %.2f\n", ans);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    printf("%d ", current[i][j]);
                }
                printf("\n");
            }
            if (ans == 0) {
                printf("Goal state reached.\n");
            }
        }
    }
    return 0;
}

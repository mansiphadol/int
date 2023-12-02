#include <stdio.h>

#define N 3

int goal[N][N];
int arr[4][2];
int mov;
float ans = 100;

float calHeuristic(int goal[N][N], int current[N][N]) {
    int dist = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist += (goal[i][j] - current[i][j]) * (goal[i][j] - current[i][j]);
        }
    }
    float hval = sqrt(dist);
    dist = 0;
    return hval;
}

void drawMatrix(int current[N][N], int x, int y, int p, int q, int temp[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == x && j == y) {
                temp[i][j] = current[p][q];
            } else if (i == p && j == q) {
                temp[i][j] = 0;
            } else {
                temp[i][j] = current[i][j];
            }
        }
    }
}

int findIndex(int i, int j, int arr[4][2]) {
    int k = 0, cnt = 0;
    if ((N > (i - 1) && i - 1 >= 0) && (N > j && j >= 0)) {
        arr[k][0] = i - 1;
        arr[k][1] = j;
        k++;
        cnt++;
    }
    if (N > i + 1 && i + 1 >= 0 && N > j && j >= 0) {
        arr[k][0] = i + 1;
        arr[k][1] = j;
        k++;
        cnt++;
    }
    if ((N > i && i >= 0) && (N > (j + 1) && j + 1 >= 0)) {
        arr[k][0] = i;
        arr[k][1] = j + 1;
        k++;
        cnt++;
    }
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
    printf("Enter initial board state: ");
    int current[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &current[i][j]);
        }
    }

    printf("Enter goal board state: ");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &goal[i][j]);
        }
    }

    ans = calHeuristic(goal, current);
    printf("Initial value: %.2f\n", ans);

    if (ans == 0) {
        printf("Initial state is the goal state.\n");
    } else {
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
        int SUCC[N][N];
        for (int i = 0; i < mov; i++) {
            int temp[N][N];
            drawMatrix(current, x, y, arr[i][0], arr[i][1], temp);
            float tans = calHeuristic(goal, temp);
            printf("value %.2f\n", tans);
            for (int k = 0; k < N; k++) {
                for (int j = 0; j < N; j++) {
                    printf("%d ", temp[k][j]);
                }
                printf("\n");
            }
            if (tans < bestHval) {
                bestHval = tans;
                for (int p = 0; p < N; p++) {
                    for (int q = 0; q < N; q++) {
                        SUCC[p][q] = temp[p][q];
                    }
                }
            }
        }
        if (bestHval >= ans) {
            printf("No operator left\n");
        } else {
            for (int p = 0; p < N; p++) {
                for (int q = 0; q < N; q++) {
                    current[p][q] = SUCC[p][q];
                }
            }
            ans = bestHval;
            printf("\nBest move: \n");
            printf("Current value: %.2f\n", ans);
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

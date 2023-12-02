#include <stdio.h>

// Function to calculate the signum function
int signum(double net) {
    if (net > 0) {
        return 1;
    }
    return -1;
}

int main() {
    double c = 0.1;
    double E = __INT_MAX__;
    int cycle = 0;

    double T[6][3] = {{0.1, 0.1, 1}, {0.2, 0.1, 1}, {0.5, 0.1, 2}, {0.6, 0.1, 2}, {0.3, 0.3, 3}, {0.4, 0.3, 3}};
    double W[3][3] = {{-0.1, 0.15, 0.2}, {-0.2, 0.11, 0.17}, {0.17, 0.16, 0.11}};
    int D[3][3] = {{1, -1, -1}, {-1, 1, -1}, {-1, -1, 1}};
    double augmented[6][4] = {{0.1, 0.1, -1, 1}, {0.2, 0.1, -1, 1}, {0.5, 0.1, -1, 2}, {0.6, 0.1, -1, 2}, {0.3, 0.3, -1, 3}, {0.4, 0.3, -1, 3}};

    int O[3];
    double net;

    while (E != 0) {
        cycle++;
        printf("Cycle number: %d\n", cycle);
        E = 0;

        for (int i = 0; i < 6; i++) {
            for (int k = 0; k < 3; k++) {
                net = 0;

                for (int j = 0; j < 3; j++) {
                    net += W[k][j] * augmented[i][j];
                }

                O[k] = signum(net);

                int wno = (int)augmented[i][3] - 1;

                if (D[wno][k] - O[k] != 0) {
                    for (int a = 0; a < 3; a++) {
                        W[k][a] = W[k][a] + 0.5 * c * (D[wno][k] - O[k]) * augmented[i][a];
                    }

                    E += 0.5 * pow(D[wno][k] - O[k], 2);
                }
            }

            for (int j = 0; j < 3; j++) {
                for (int a = 0; a < 3; a++) {
                    printf("%f ", W[j][a]);
                }
                printf("\n");
            }

            printf("Error : %f\n", E);
        }

        printf("Cumulative Error after cycle %d: %f\n", cycle, E);
        printf("Weight Matrix after cycle %d:\n", cycle);

        for (int i = 0; i < 3; i++) {
            for (int a = 0; a < 3; a++) {
                printf("%f ", W[i][a]);
            }
            printf("\n");
        }
    }

    printf("Cycles required: %d\n", cycle);

    return 0;
}

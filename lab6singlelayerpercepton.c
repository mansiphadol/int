#include <stdio.h>

// Function to calculate the signum function
int sgn(double netValue) {
    if (netValue > 0)
        return 1;
    else
        return -1;
}

int main() {
    double X[3][4] = {
        {1, -2, 1.5, 0},
        {1, -0.5, -2, -1.5},
        {0, 1, -1, 1.5}
    }; // input matrix

    double w[4] = {1, -1, 0, 0.5}; // initial weight vector
    int d[3] = {1, -1, 1}; // desired output

    double c = 1; // learning rate > 0
    double net, output;
    int i, j, k;
    double error;
    int cycles = 0;

    printf("Initial weight vector: ");
    for (i = 0; i < 4; i++) {
        printf("%f ", w[i]);
    }
    printf("\n");

    do {
        cycles++; // Increment the cycle count

        // Print cycle information
        printf("Epoch: %d\n", cycles);
        error = 0; // Reset error for the current cycle

        for (i = 0; i < 3; i++) {
            net = 0;

            // Calculate net
            for (j = 0; j < 4; j++) {
                net += X[i][j] * w[j];
            }

            // Calculate output using signum function
            output = sgn(net);

            if (output != d[i]) {
                // Update weights
                for (k = 0; k < 4; k++) {
                    w[k] += c * (d[i] - output) * X[i][k];
                }
            }

            // Calculate error for the current input
            double xError = d[i] - output;
            printf("Error for X%d: %f\n", i + 1, xError);

            // Print weight vector for the current input
            printf("Weight vector : ");
            for (k = 0; k < 4; k++) {
                printf("%f ", w[k]);
            }
            printf("\n");

            // Accumulate absolute error
            error += xError;
        }

        printf("Total Error: %f\n", error);

    } while (error != 0); // Continue until error is not 0

    printf("Cycles required: %d\n", cycles);

    printf("Final weight vector: ");
    for (i = 0; i < 4; i++) {
        printf("%f ", w[i]);
    }

    return 0;
}

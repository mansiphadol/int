#include <stdio.h>

int main() {
    double r = 1;
    double x;
    
    printf("Enter number whose membership is to be calculated: ");
    scanf("%lf", &x);

    double a = 5 / fmax(x, 5);
    double b = x / fmax(x, 5);
    double y = r * (fabs(a - b));
    double v = 1 - y;

    if (y == 0) {
        printf("Full Member\n");
    } else if (0 < y && y < 1) {
        printf("Membership Value: %lf\n", v);
    } else if (y >= 1) {
        printf("Non Member\n");
    }

    return 0;
}

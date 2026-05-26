#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INTERVAL 10000
#define TOTAL_POINTS 100000000

int main() {
    int i;
    double rand_x, rand_y, distancia_origem, pi;
    int circle_points = 0;

    srand(time(NULL));

    for (i = 0; i < (TOTAL_POINTS); i++) {

        rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL;
        rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL;

        distancia_origem = rand_x * rand_x + rand_y * rand_y;

        if (distancia_origem <= 1)
            circle_points++;
    }

    pi = 4.0 * circle_points / TOTAL_POINTS;

    printf("Estimativa de PI = %f\n", pi);

    return 0;
}
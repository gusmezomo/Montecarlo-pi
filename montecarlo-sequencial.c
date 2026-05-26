#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INTERVALO 10000
#define TOTAL_PONTOS 100000000

int main() {
    int i;
    double rand_x, rand_y, distancia_origem, pi;
    int pontos_circulo = 0;

    srand(time(NULL));

    for (i = 0; i < (TOTAL_PONTOS); i++) {

        rand_x = (double)(rand() % (INTERVALO + 1)) / INTERVALO;
        rand_y = (double)(rand() % (INTERVALO + 1)) / INTERVALO;

        distancia_origem = rand_x * rand_x + rand_y * rand_y;

        if (distancia_origem <= 1)
            pontos_circulo++;
    }

    pi = 4.0 * pontos_circulo / TOTAL_PONTOS;

    printf("Estimativa de PI = %f\n", pi);

    return 0;
}
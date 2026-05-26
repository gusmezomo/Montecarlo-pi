// gcc montecarlo-paralelo.c -o paralelo -fopenmp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define INTERVAL 10000
#define TOTAL_POINTS 100000000

int main() {
    int i;
    double rand_x, rand_y, distancia_origem, pi;
    int circle_points = 0;

    omp_set_num_threads(8);

    srand(time(NULL));

    #pragma omp parallel reduction(+:circle_points) 
    {
        // cria uma seed diferente para cada thread usando o tempo atual + id da thread
        unsigned int seed = time(NULL) + omp_get_thread_num();

        #pragma omp for schedule(static,1) //schedule(static,1) - PARA DISTRUBUIR AS THREADS ALTERNADAMENTE
        for (i = 0; i < (TOTAL_POINTS); i++) {

            //imprimir as 20 primeiras interaçoes
            int thread_id = omp_get_thread_num();
            if (i < 20) {
                printf("Iteracao %d -> Thread %d\n", i, thread_id);
            }

            rand_x = (double)(rand_r(&seed) % (INTERVAL + 1)) / INTERVAL;
            rand_y = (double)(rand_r(&seed) % (INTERVAL + 1)) / INTERVAL;

            distancia_origem = rand_x * rand_x + rand_y * rand_y;

            if (distancia_origem <= 1)
                circle_points++;
        }
    }

    pi = 4.0 * circle_points / TOTAL_POINTS;

    printf("Estimativa de PI = %f\n", pi);
    printf("Numero de threads gerados: %d\n", omp_get_max_threads());

    return 0;
}
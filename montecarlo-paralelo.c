// gcc montecarlo-paralelo.c -o paralelo -fopenmp
//DEFINIR AS THREADS NA EXECUCAO:
//OMP_NUM_THREADS=4 ./paralelo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define INTERVALO 10000
#define TOTAL_PONTOS 500000000

int main() {
    double inicio, fim; //variaveis para medir o tempo de execucao

    int i;
    double rand_x, rand_y, distancia_origem, pi;
    int pontos_circulo = 0;

    inicio = omp_get_wtime();

    #pragma omp parallel reduction(+:pontos_circulo) 
    {
        #pragma omp single
        {
            printf("Numero de threads gerados: %d\n", omp_get_num_threads());
        }

        // cria uma seed única para cada thread usando o tempo atual e o id da thread
        unsigned int seed = time(NULL) + omp_get_thread_num();

        #pragma omp for //schedule(static,1) //schedule(static,1) - PARA DISTRUBUIR AS THREADS ALTERNADAMENTE
        for (i = 0; i < (TOTAL_PONTOS); i++) {

            //imprimir as 20 primeiras interaçoes
            //removido para fazer testes de speedup
            // int thread_id = omp_get_thread_num();
            // if (i < 20) {
            //     printf("Iteracao %d -> Thread %d\n", i, thread_id);
            // }

            rand_x = (double)(rand_r(&seed) % (INTERVALO + 1)) / INTERVALO;
            rand_y = (double)(rand_r(&seed) % (INTERVALO + 1)) / INTERVALO;

            distancia_origem = rand_x * rand_x + rand_y * rand_y;

            if (distancia_origem <= 1)
                pontos_circulo++;
        }
    }

    pi = 4.0 * pontos_circulo / TOTAL_PONTOS;

    printf("Estimativa de PI = %f\n", pi);

    fim = omp_get_wtime();

    printf("Tempo: %f\n", fim - inicio);
    
    return 0;
}
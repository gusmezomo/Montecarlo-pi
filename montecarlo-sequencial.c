//gcc montecarlo-sequencial.c -o sequencial -fopenmp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//incluido a biblioteca apenas para a funcao:
//"omp_get_wtime();" para contar o tempo de execução,
//sendo uma comparacao consistente entre os codigos.
#include <omp.h> 

#define INTERVALO 10000
#define TOTAL_PONTOS 100000000

int main() {
    double inicio, fim; //variaveis para medir o tempo de execucao
    
    int i;
    double rand_x, rand_y, distancia_origem, pi;
    int pontos_circulo = 0;

    srand(time(NULL));

    inicio = omp_get_wtime();

    for (i = 0; i < (TOTAL_PONTOS); i++) {

        rand_x = (double)(rand() % (INTERVALO + 1)) / INTERVALO;
        rand_y = (double)(rand() % (INTERVALO + 1)) / INTERVALO;

        distancia_origem = rand_x * rand_x + rand_y * rand_y;

        if (distancia_origem <= 1)
            pontos_circulo++;
    }

    pi = 4.0 * pontos_circulo / TOTAL_PONTOS;

    printf("Estimativa de PI = %f\n", pi);

    fim = omp_get_wtime();

    printf("Tempo: %f\n", fim - inicio);

    return 0;
}
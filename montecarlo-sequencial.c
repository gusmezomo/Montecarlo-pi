// Gustavo Mezomo e Pedro Gustavo Thomas

// Compilar:
// gcc montecarlo-sequencial.c -o sequencial -fopenmp

// Executar:
// ./sequencial

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// incluido apenas para medir o tempo de execução.
#include <omp.h>

// valor usado para gerar números aleatórios entre 0 e 1.
#define INTERVALO 10000

// quantidade total de pontos que serão gerados na simulação.
#define TOTAL_PONTOS 1000000000

int main() {
    // variáveis usadas para medir o tempo de execução.
    double inicio, fim;

    int i;

    // coordenadas do ponto gerado, valor da distância ao quadrado
    // até a origem e valor final estimado de PI.
    double rand_x, rand_y, distancia_quadrada, pi;

    // conta quantos pontos caíram dentro do círculo.
    int pontos_circulo = 0;

    // inicio, contar tempo de exec
    inicio = omp_get_wtime();

    // cria a seed inicial para o gerador de números aleatórios
    // usando o horário atual do sistema.
    unsigned int seed = time(NULL);

    // gera os pontos da simulação.
    for (i = 0; i < TOTAL_PONTOS; i++) {
        // gera um valor aleatório para X entre 0 e 1.
        rand_x = (double)(rand_r(&seed) % (INTERVALO + 1)) / INTERVALO;
        // gera um valor aleatório para Y entre 0 e 1.
        rand_y = (double)(rand_r(&seed) % (INTERVALO + 1)) / INTERVALO;

        // calcula a distância ao quadrado entre o ponto gerado e a origem (0,0).
        distancia_quadrada = rand_x * rand_x + rand_y * rand_y;

        // se a distância ao quadrado for menor ou igual a 1,
        // o ponto está dentro do círculo.
        if (distancia_quadrada <= 1)
            pontos_circulo++;
    }

    printf("Total de pontos gerados: %d\n", TOTAL_PONTOS);
    
    // calcula a estimativa de PI
    pi = 4.0 * pontos_circulo / TOTAL_PONTOS;

    // exibe o valor estimado de PI.
    printf("Estimativa de PI = %f\n", pi);

    // fim, contar tempo de exec
    fim = omp_get_wtime();

    // exibe tempo total de execução
    printf("Tempo: %f\n", fim - inicio);

    return 0;
}
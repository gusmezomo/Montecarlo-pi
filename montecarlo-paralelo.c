// Gustavo Mezomo e Pedro Gustavo Thomas

// Compilar:
// gcc montecarlo-paralelo.c -o paralelo -fopenmp

// Executar definindo a quantidade de threads:
// OMP_NUM_THREADS=4 ./paralelo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// valor usado para gerar números aleatórios entre 0 e 1.
#define INTERVALO 10000

// quantidade total de pontos que serão gerados na simulação.
#define TOTAL_PONTOS 1000000000

int main() {
    // variáveis usadas para medir o tempo de execução.
    double inicio, fim;

    int i;

    // coordenadas do ponto gerado, distância ao quadrado
    // até a origem e valor final estimado de PI.
    double rand_x, rand_y, distancia_quadrada, pi;

    // conta quantos pontos caíram dentro do círculo.
    int pontos_circulo = 0;

    // inicio, contar tempo de exec
    inicio = omp_get_wtime();

    // inicia a região paralela.
    // cria as threads e cada uma executará uma parte do trabalho.
    //
    // o "reduction" garante que cada thread tenha
    // seu próprio contador de pontos e que todos os valores
    // sejam somados corretamente ao final.
    #pragma omp parallel reduction(+:pontos_circulo)
    {
        // apenas uma thread executa este bloco.
        // serve apenas para mostrar quantas threads foram criadas
        // sem isso, todas as threads iam mostrar o "print", mostrando 4x
        #pragma omp single
        {
            printf("Numero de threads gerados: %d\n", omp_get_num_threads());
        }

        // cria uma seed diferente para cada thread.
        // isso evita que duas threads gerem exatamente
        // a mesma sequência de números aleatórios.
        unsigned int seed = time(NULL) + omp_get_thread_num();

        // divide as iterações do laço entre as threads disponíveis.
        #pragma omp for
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
    }
    
    printf("Total de pontos gerados: %d\n", TOTAL_PONTOS);

    //calcula a estimativa de PI
    pi = 4.0 * pontos_circulo / TOTAL_PONTOS;

    // exibe o valor estimado de PI.
    printf("Estimativa de PI = %f\n", pi);

    // fim, contar tempo de exec
    fim = omp_get_wtime();

    // exibe tempo total de execução
    printf("Tempo: %f\n", fim - inicio);

    return 0;
}
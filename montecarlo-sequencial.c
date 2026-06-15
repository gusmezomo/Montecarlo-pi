// Gustavo Mezomo e Pedro Gustavo Thomas

// Compilar:
// gcc montecarlo-sequencial.c -o sequencial -fopenmp

// Executar:
// ./sequencial

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Biblioteca utilizada apenas para medir o tempo de execução.
#include <omp.h>

// Valor usado para gerar números aleatórios entre 0 e 1.
#define INTERVALO 10000

// Quantidade total de pontos que serão gerados na simulação.
#define TOTAL_PONTOS 1000000000

int main() {
    // variáveis usadas para medir o tempo de execução.
    double inicio, fim;

    int i;

    // Coordenadas do ponto gerado, valor da distância ao quadrado
    // até a origem e valor final estimado de PI.
    double rand_x, rand_y, distancia_quadrada, pi;

    // Conta quantos pontos caíram dentro do círculo.
    int pontos_circulo = 0;

    // Marca o instante em que o programa começou.
    inicio = omp_get_wtime();

    // Cria a seed inicial para o gerador de números aleatórios
    // usando o horário atual do sistema.
    unsigned int seed = time(NULL);

    // Gera todos os pontos da simulação.
    for (i = 0; i < TOTAL_PONTOS; i++) {

        // Gera um valor aleatório para X entre 0 e 1.
        rand_x = (double)(rand_r(&seed) % (INTERVALO + 1)) / INTERVALO;

        // Gera um valor aleatório para Y entre 0 e 1.
        rand_y = (double)(rand_r(&seed) % (INTERVALO + 1)) / INTERVALO;

        // Calcula a distância ao quadrado entre o ponto gerado
        // e a origem (0,0). Não é necessário calcular a raiz
        // quadrada para verificar se o ponto está dentro do círculo.
        distancia_quadrada = rand_x * rand_x + rand_y * rand_y;

        // Se a distância ao quadrado for menor ou igual a 1,
        // o ponto está dentro do círculo de raio 1.
        if (distancia_quadrada <= 1)
            pontos_circulo++;
    }

    // Calcula a estimativa de PI utilizando a proporção
    // entre os pontos dentro do círculo e o total de pontos.
    pi = 4.0 * pontos_circulo / TOTAL_PONTOS;

    // Exibe o valor estimado de PI.
    printf("Estimativa de PI = %f\n", pi);

    // Marca o instante em que o programa terminou.
    fim = omp_get_wtime();

    // Mostra o tempo total de execução em segundos.
    printf("Tempo: %f\n", fim - inicio);

    return 0;
}
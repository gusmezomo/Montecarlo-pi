// Gustavo Mezomo e Pedro Gustavo Thomas

// Compilar:
// gcc montecarlo-paralelo.c -o paralelo -fopenmp

// Executar definindo a quantidade de threads:
// OMP_NUM_THREADS=4 ./paralelo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Valor usado para gerar números aleatórios entre 0 e 1.
#define INTERVALO 10000

// Quantidade total de pontos que serão gerados na simulação.
#define TOTAL_PONTOS 1000000000

int main() {

    // Variáveis usadas para medir o tempo de execução.
    double inicio, fim;

    // Variável de controle do laço.
    int i;

    // Coordenadas do ponto gerado, distância ao quadrado
    // até a origem e valor final estimado de PI.
    double rand_x, rand_y, distancia_quadrada, pi;

    // Conta quantos pontos caíram dentro do círculo.
    int pontos_circulo = 0;

    // Marca o instante em que o programa começou.
    inicio = omp_get_wtime();

    // Inicia uma região paralela.
    // O OpenMP cria as threads e cada uma executará uma parte do trabalho.
    //
    // A cláusula reduction garante que cada thread tenha
    // seu próprio contador de pontos e que todos os valores
    // sejam somados corretamente ao final.
    #pragma omp parallel reduction(+:pontos_circulo)
    {

        // Apenas uma thread executa este bloco.
        // Serve apenas para mostrar quantas threads foram criadas pelo OpenMP.
        // Sem isso, todas as threads iam mostrar o "print", mostrando 4x no terminal
        #pragma omp single
        {
            printf("Numero de threads gerados: %d\n",
                   omp_get_num_threads());
        }

        // Cria uma seed diferente para cada thread.
        // Isso evita que duas threads gerem exatamente
        // a mesma sequência de números aleatórios.
        unsigned int seed =
            time(NULL) + omp_get_thread_num();

        // Divide automaticamente as iterações do laço
        // entre as threads disponíveis.
        #pragma omp for
        for (i = 0; i < TOTAL_PONTOS; i++) {

            // Gera um valor aleatório para X entre 0 e 1.
            rand_x = (double)(rand_r(&seed) %
                     (INTERVALO + 1)) / INTERVALO;

            // Gera um valor aleatório para Y entre 0 e 1.
            rand_y = (double)(rand_r(&seed) %
                     (INTERVALO + 1)) / INTERVALO;

            // Calcula a distância ao quadrado do ponto
            // até a origem (0,0).
            distancia_quadrada =
                rand_x * rand_x + rand_y * rand_y;

            // Se o ponto estiver dentro do círculo,
            // incrementa o contador local da thread.
            if (distancia_quadrada <= 1)
                pontos_circulo++;
        }
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
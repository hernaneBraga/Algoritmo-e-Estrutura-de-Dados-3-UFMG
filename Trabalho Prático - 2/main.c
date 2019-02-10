/*  Programa desenvolvido por Hernane Braga Pereira - Engenharia de Sistemas - UFMG
    Trabalho pratico 2 da disciplina Algoritmos e Estruturas de Dados 3 
    Os codigos implementados sao baseados e inpirados das seguintes fontes:

    - Artigo sobre algoritmo Levenshtein Distance: https://en.wikipedia.org/wiki/Levenshtein_distance
    - Implementação do algoritmo usado na função deste trabalho: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
    - Geeks for geeks: https://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance/
    - Ordenação de struct em C: https://stackoverflow.com/questions/34281390/how-to-sort-struct-by-grade-and-last-name-alphabetically
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "levinstain.h"

int main(){

    /* Variavel para calculo de tempo de execucao do programa */
    /* Deve ser usada em conjunto com o trecho de codigo comentado, após fim do código do TP2 */
    //clock_t begin = clock();

    int tam_dicionario, max_mudancas, i, distancia, num_linhas = 0;

    /* Limites de strings informadas pelo monitor no forum do moodle UFMG */
    char palavra_consulta[100], palavra_dicionario[10000];

    item *lista_resultados = malloc(sizeof(item));

    /* Leituda dos dados de entrada do arquivo */
    scanf("%d", &tam_dicionario);


    scanf("%d", &max_mudancas);
    scanf("%s", palavra_consulta);

    /* Loop para ler as entradas do dicionario */
    for ( i = 0; i < tam_dicionario; i++ ){

        scanf("%s", palavra_dicionario);

        /* Calcula o numero de mudancas(distancia) entre a palavra do dicionario e a buscada */
        distancia = levenshtein(palavra_consulta, palavra_dicionario); 

        if ( distancia <= max_mudancas){

            /* Se for a primeira vez, salva a palavra e distancia na struct */
            if ( num_linhas == 0){
                strcpy(lista_resultados[num_linhas].palavra, palavra_dicionario);
                lista_resultados[num_linhas].distancia = distancia;
            }

            /* Senao for, realoca o tamanho da estrutura e salva os dados */
            else{

                lista_resultados = realloc( lista_resultados, (num_linhas + 1) * sizeof(item));
                strcpy(lista_resultados[num_linhas].palavra, palavra_dicionario);
                lista_resultados[num_linhas].distancia = distancia;
            }

            num_linhas++;
        }
    }

    /* Ordenação e impressão da lista com os resultados */
    qsort(lista_resultados, num_linhas, sizeof(item), cmp_palavras); 
    impressao_final(lista_resultados, num_linhas);

    /* Desalocando memoria */   
    free(lista_resultados);

    /* -------------------------------------------------------- */
    /* -------------------------------------------------------- */

    /*  FIM DO TP 2 - ABAIXO, APENAS CODIGOS USADOS PARA GERAR TESTES */
    
    /* -------------------------------------------------------- */
    /* -------------------------------------------------------- */

    /* Calculo do tempo gasto pelo programa em mili segundos */
    /* Retirar comentário para ter esta informação */
    /*
    clock_t end = clock();
    double time_spent = (double)(end - begin) ;
    printf("\n__________________________\n\n==== RESUMO ====\n");
    printf("TEMPO = %.4f milisegundos\n", (time_spent / CLOCKS_PER_SEC) *1000 ) ;
    printf("DICIONARIO = %d\nPALAVRAS ENCONTRADAS = %d\n__________________________\n", tam_dicionario, num_linhas);
    */


    
}
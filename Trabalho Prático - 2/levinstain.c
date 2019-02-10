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

/* Definicao que serve de suporte para o algoritmo Levenshtein Distance */
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

/* Função de ordenação de estrutura usada pelo qsort */ 
int cmp_palavras(const void *p1, const void *p2){
    item *l = (item *)p1;
    item *r = (item *)p2;
    if (l->distancia == r->distancia)
    {
        return strcmp(l->palavra, r->palavra);
    }
    return (l->distancia > r->distancia)?(1):(-1);
}

/* Função para imprimir a lista de palavras na tela */ 
void impressao_final( item *lista_impressao, int quantidade){

    int i;
    for( i = 0 ; i < quantidade ; i++)
        printf("%s\n", lista_impressao[i].palavra);
}

/* Algoritmo Levenshtein para calcular distancia entre strings */ 
int levenshtein(char *s1, char *s2) {
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return(column[s1len]);
}

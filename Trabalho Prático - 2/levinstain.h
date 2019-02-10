/*  Programa desenvolvido por Hernane Braga Pereira - Engenharia de Sistemas - UFMG
    Trabalho pratico 2 da disciplina Algoritmos e Estruturas de Dados 3 
    Os codigos implementados sao baseados e inpirados das seguintes fontes:

    - Artigo sobre algoritmo Levenshtein Distance: https://en.wikipedia.org/wiki/Levenshtein_distance
    - Implementação do algoritmo usado na função deste trabalho: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
    - Geeks for geeks: https://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance/
    - Ordenação de struct em C: https://stackoverflow.com/questions/34281390/how-to-sort-struct-by-grade-and-last-name-alphabetically
*/

/* Estrutura para armazenar os dados de saida */ 
typedef struct{ 
    char palavra[10000];
    int  distancia;
} item;

void impressao_final( item *lista_impressao, int quantidade);
int levenshtein(char *s1, char *s2);
int cmp_palavras(const void *p1, const void *p2);
/*  Programa desenvolvido por Hernane Braga Pereira - Engenharia de Sistemas - UFMG
    Trabalho pratico 3 da disciplina Algoritmos e Estruturas de Dados 3 
    Os codigos implementados sao baseados e inpirados das seguintes fontes:

    - Permutacao de strings: https://www.quora.com/How-do-I-write-a-program-to-display-the-permutation-of-n-numbers-in-C
*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h" // Biblioteca de grafos


typedef int bool;
#define true 1
#define false 0

int cont_rodadas=0;

// Funcao suporte para ordenar vetor de cores em ordem crescente para a funcao qsort
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}


/* Funcao que imprime o resultado final nos dois arquivos especificados */
void printSolution(int color[], int V)
{
    int i;
    FILE *fp = fopen("alocacao.txt", "w"); 
    for (i = 0; i < V; i++)
      fprintf(fp, "%d %d\n", i+1, color[i]);
    fclose(fp);

    fp = fopen("rodada.txt", "w");
    fprintf(fp, "%d\n", cont_rodadas);
    fclose(fp);
}


/* Funcao que verifica a solucao proposta */
bool isSafe (struct Graph* graph)
{   
    int v;

    // Verifica a possibilidade em todos os vertices
    for (v = 0 ; v < graph->V; v++){
        
        // Verifica a possibilidade em todos os adjacentes daquele vertice
        struct AdjListNode* pCrawl = graph->array[v].head;

        while (pCrawl){
            if ( graph->array[v].cor == graph->array[pCrawl->dest].cor ){
                //printf("Vertices [%d] e [%d] estao com a mesma cor %d. \n", v+1, pCrawl->dest+1, graph->array[v].cor);
                return false;
            }  
            
            pCrawl = pCrawl->next;
        }
    }

    return true;
}

/* Funcao que atribui cores ao grafo, dado um vetor de cores */
void colorir_grafo(int arr[], struct Graph* graph)
{
    int i;
    for( i = 0 ; i < graph->V ; i++)
        graph->array[i].cor = arr[i];
    
}

/* Funcao de suporte para trocar variaveis na permutacao */
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/* Funcao que faz a permutacao do vetor de entrada e retorna se uma das permutacoes é solucao */
bool permutation(int *arr, int start, int end, struct Graph* graph)
{
    
    int retorno = false;
    int i;

    // Verifica se a solucao e possivel
    if (isSafe(graph) == true){
        retorno = true;
        return true;
    }
    
    // Se uma nova permutacao foi finalizada, entao colore o grafo com a candidata a solucao
    if(start==end)
        colorir_grafo(arr, graph);   
    
    
    for( i = start ; i <= end ; i++)
    {
        swap((arr+i), (arr+start));

        // Se permutacao encontrada for verdadeira, retorna true
        if( permutation(arr, start+1, end, graph) == true){
            return true;
        }

        swap((arr+i), (arr+start));
    }
    return retorno;
}

int main()
{
    
    int aux1, aux2, num_conexoes, num_servidores;

    scanf("%d%d", &num_servidores, &num_conexoes);
    struct Graph* graph = createGraph(num_servidores);

    int size = num_servidores;

    int i, j, limite_inferior = 0;
    int arr[size];


    // Popula o grafo
    for ( i = 0 ; i < num_conexoes ; i++){
        scanf("%d%d", &aux1, &aux2);
        addEdge(graph, aux1-1, aux2-1); // Dados de entrada comecao em 1, entao subtraimos 1 para 
                                        // os indices do arquivo de origem e de nosso grafo serem iguais.
    }

    // Inicializa o vetor de cores com 1
    for ( i = 0 ; i < size ;i++)
        arr[i] = 1;


    j = size - 1; 
    limite_inferior = 0;
    bool parada = false;

    // Verifica todas as solucoes
    while( parada == false){
        
        // Faz a permutacao no vetor de cores que é candidato a soluçao
        parada = permutation(arr, 0, size-1, graph);

        // Se encontrar uma solucao, entao ela e otima e saimos do loop
        if ( parada == true){
            break;
        }
        
        // Ordenar o vetor de saida em ordem crescente para acrescentar nova cor
        qsort(arr, size, sizeof(int), cmpfunc);

        if ( j == limite_inferior){
            j = size - 1;
            limite_inferior++;
        }
        else{
            arr[j] = arr[limite_inferior] + 1;
            cont_rodadas =   arr[j];
            j--;
        }

    }

    // Imprime solucao otima encontrada
    printSolution(arr, size);
    free_graph(graph);

    return 0;
}
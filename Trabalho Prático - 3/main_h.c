/*  Programa desenvolvido por Hernane Braga Pereira - Engenharia de Sistemas - UFMG
    Trabalho pratico 3 da disciplina Algoritmos e Estruturas de Dados 3 
    Os codigos implementados sao baseados e inpirados das seguintes fontes:

    - Geeks for geeks coloração usando backtracking em matriz de adj: https://www.geeksforgeeks.org/backttracking-set-5-m-coloring-problem/
*/

#include<stdio.h>
#include<stdlib.h>
#include "graph.h" // Biblioteca de grafos

typedef int bool;
#define true 1
#define false 0

int cont_rodadas = 0; 

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


/* Uma funcao auxiliar para verificar se a cor atual pode ser atribuida ao vertice */
bool isSafe (int v, struct Graph* graph, int color[], int c)
{

    struct AdjListNode* pCrawl = graph->array[v].head;
    
    // Verifica se o vertice atual pode receber esta cor 
    if (graph->array[v].cor && c == color[v]) 
            return false;
    
    // Se puder, olhamos os demais vertices adjacentes
    while (pCrawl){

        if (graph->array[ pCrawl->dest ].cor && c == color[ pCrawl->dest ]) 
            return false;
        
        pCrawl = pCrawl->next;
    }

    return true;
}


/* Funcao recursiva usada para solucionar o problema de colorir usando m cores */
bool graphColoringUtil(struct Graph* graph, int m, int color[], int v)
{
    /* Caso base: Se todos os vertices possuirem uma cor
       return true */
    if (v == graph->V)
        return true;
 
    int c;
    /* Considere este vertice v e tenta-se cores diferentes */
    for (c = 1; c <= m; c++)
    {

        /* Verifica-se se e possivel atribuir a cor c ao vertice v */
        if (isSafe(v, graph, color, c))
        {
            color[v] = c;
            graph->array[v].cor = c;
          
            if ( c >= cont_rodadas)
                cont_rodadas = c;
 
           /* Chama a mesma funcao para o proximo vertice */
           if (graphColoringUtil (graph, m, color, v+1) == true)
             return true;
           
          /* Se a cor escolhida c nao leva a uma solucao, entao eh removida */
           color[v] = 0;
           graph->array[v].cor = 0;
     
        }
    }
    /* Senao pudermos atribuir uma cor ao vertice, retorna false */
    return false;
}

/* Esta funcao resolve o problema de colorir um grafo usando ate m cores, atraves do metodo de backtracking
  É utilizada principalmente a funcao graphColoringUtil() para resolver o problema. 
  Ela retorna false senao for possivel colorir o grafo usando m cores, do contrario returna true e
  os arquivos rodada.txt e alocacao.txt serao impressos. Importante ressaltar que podem haver mais de 
  uma solucao para o problema e ao final e impresso uma destas possiveis solucoes.
*/
bool graphColoring(struct Graph* graph)
{
    // Cria o vetor que armazenara as cores de cada vertice e os inicializa com 0
    int num_vertices = graph->V;
    int color[num_vertices];
    int i;
    
    for (i = 0 ; i < num_vertices ; i++)
       color[i] = 0;
 
    // Comeca o algoritmo de coloracao no vertice 0
    // Como nao ha um limite m de cores a serem utilizadas, passamos o nº de vertices como parametro
    if (graphColoringUtil(graph, num_vertices, color, 0) == false)
      return false;
    
    // Imprime a solucao nos dois arquivos pedidos: rodada.txt e alocacao.txt
    printSolution(color, graph->V);
    return true;
}

int main(){

    int num_servidores, num_conexoes;
    int i;
    int aux1, aux2;

    // Recebe o numero de vertices e arestas que o grafo possui
    scanf("%d%d", &num_servidores, &num_conexoes);
    struct Graph* graph = createGraph(num_servidores);

    // Popula o grafo
    for ( i = 0 ; i < num_conexoes ; i++){
        scanf("%d%d", &aux1, &aux2);
        addEdge(graph, aux1-1, aux2-1); // Dados de entrada comecao em 1, entao subtraimos 1 para 
                                        // os indices do arquivo de origem e de nosso grafo serem iguais.
    }

    graphColoring(graph); // Chama a funcao que calculará o numero de rodadas de atualizacao nos servidores
    free_graph(graph);  // Desaloca o grafo criado

    return 0;
}
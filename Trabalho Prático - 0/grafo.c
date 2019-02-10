/*  Programa desenvolvido por Hernane Braga Pereira - Engenharia de Sistemas - UFMG
    Trabalho pratico 0 da disciplina Algoritmos e Estruturas de Dados 3 
    Os codigos implementados sao baseados e inpirados das seguintes fontes:

    - IME-USP: https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html#GRAPHinit-lists
    - Programacao descomplicada em C: https://www.youtube.com/watch?v=gJvSmrxekDo&list=PL8iN9FQ7_jt4oQHq1TSeMgvVdolJvYsLO
    - Geeks for geeks: https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/
    - Livro: Projeto de Algoritmos do autor Nivio Ziviani
*/
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// Cria novo no na lista de adjacencia, dado um vertice de destino (dest)
struct AdjListNode* newAdjListNode( int dest){
    struct AdjListNode* newNode =
     (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
// Inicializa o grafo
Graph cria_grafo( int V){
    Graph graph = malloc(sizeof *graph);
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of 
    // array will be V
    graph->array = 
      (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    // Initialize each adjacency list as empty by 
    // making head as NULL
    int i;
    for (i = 0; i < V; ++i){
        graph->array[i].head = NULL;
        graph->array[i].grau = 0;
        graph->array[i].visitado = -1;
    }
 
    return graph;
}
 
// Adds an edge to an undirected graph
void add_aresta( Graph graph, int src, int dest){
    // Add an edge from src to dest.  A new node is 
    // added to the adjacency list of src.  The node
    // is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    graph->array[src].grau++;
 
    // Since graph is undirected, add an edge from
    // dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
    graph->array[dest].grau++;
}

// Adiciona id e idade de uma pessoa
void add_id_idade( Graph graph, int src, int id, int idade){
    graph->array[src].id_pessoa = id;
    graph->array[src].idade = idade;
}

// Verifica se o id informado e valido, e se sim, retorna seu indx de vertice
int verifica_id( Graph graph, int id_pessoa){
    int i;
    for ( i = 0; i < graph->V; i++){
        if ( graph->array[i].id_pessoa == id_pessoa)
            return i;
    }
    return -1;
}
 
// Funcao para imprimir o grafo
void printGraph( Graph graph){
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

/* 
Conta quantas pessoas gostaram da musica, a partir de um index (indx) de um vertice 
E pedido um contado (*cont) para contar quantas pessoas gostaram da musica
O parametro aux deve ser enviado com -1 por default
*/
void conta_musica( Graph graph, int indx, int *cont, int aux){
    int i;
    //printf("\n\tAlgoritmo Busca musica");

    // Realiza i verificacoes, baseado no grau do vertice
    for ( i = 0; i < graph->array[indx].grau; i++)
    {
        // pCrawl recebe o valor do index da celula visitada dentro da lista encadeada
        struct AdjListNode* pCrawl = graph->array[indx].head;
        graph->array[indx].visitado = 1; //index e marcado como visitado

        //printf("\n--- Entrou no vertice [%d] ---\n", indx);
        
        // Loop ocorre enquanto nao puder apontar para mais nada ( pCrawl != NULL )
        while (pCrawl)
        {
            aux = pCrawl->dest;
            // Verifica se o proximo no ainda nao foi visitado. Senao, chama a funcao recursivamente.
            if ( graph->array[aux].visitado == -1){  
                conta_musica(graph, aux, cont, aux);
            }
            else{
                pCrawl = pCrawl->next;     
            }     
        }      
    }
    cont[0] +=1;
   // printf("cont = %d\n\n", *cont);
}


// Funcao para desalocar o grafo da memoria
void deleta_grafo( Graph graph, int i){


    struct AdjListNode* pCrawl = graph->array[i].head;

    if ( pCrawl != NULL){
        if ( pCrawl->next != NULL){
            deleta_grafo( graph, pCrawl->dest);
        }
        else {
            free(pCrawl);
        }
    }
    free( graph);  
}

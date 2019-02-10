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
 
// Representacao do no da lista
struct AdjListNode{
    int dest;
    struct AdjListNode* next;
};
 
// Representacao da lista encadeada
struct AdjList{
    struct AdjListNode *head; 
    int id_pessoa;
    int idade;
    int visitado; // Se ja foi visitado durante a busca. Inicializa com -1.
    int grau; // Quantas conexoes o vertice ja possui
};

// Estrutura do grafo com V (vertices) e lista de adjacencia
struct graph{
    int V;
    struct AdjList* array;
};

typedef struct graph *Graph;


struct AdjListNode* newAdjListNode( int dest);
Graph cria_grafo( int V);
void add_aresta( Graph graph, int src, int dest);
void add_id_idade( Graph graph, int src, int id, int idade);
int verifica_id( Graph graph, int id_pessoa);
void printGraph( Graph graph);
void conta_musica( Graph graph, int indx, int *cont, int aux);
void deleta_grafo( Graph graph, int i);


/*
Estrutura base de um grafo foi inspirada no site Geeks for Geeks. Fontes: 
Estrutura de grafos: https://www.geeksforgeeks.org/graph-and-its-representations/
Remoção de grafo: https://ideone.com/XfdwKE
*/

#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
     (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = 
        (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = 0;
 
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
        graph->array[i].cor = -1;
    }
 
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    graph->E++;
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
 
// A utility function to print the adjacency list 
// representation of graph
void printGraph(struct Graph* graph)
{
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


// Retirado e adaptado de: https://ideone.com/XfdwKE
void free_graph(struct Graph* graph)
{
    int i;
    /* free the graph in a bottom up manner */
    if (graph == NULL) return ;
    struct AdjListNode *cursor, *temp;
    for (i = 0; i < graph->V; i++) {
        cursor = graph->array[i].head;
        while (cursor != NULL) {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
    graph = NULL;
}
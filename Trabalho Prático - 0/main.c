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

int main(  )
{

    FILE *arquivo;

    arquivo = stdin;
 
    //Leitura dos dados do arquivo
    int i, vertices, arestas, id, idade, aux;
    int vertices_validos = 0; //Pessoas com idade < 35 anos

    fscanf(arquivo, "%d %d", &vertices, &arestas);

    //Verificar quantas pessoas tem idade < 35
    //Assim criamos o grafo com a quantidade minima de espaco
    for( i = 0 ; i < vertices ; i++){
        fscanf(arquivo,"%d %d", &id, &idade);
        if( idade < 35){
            vertices_validos++;
        }
    }

    //Voltar para o inicio do arquivo e comeca a ler-lo novamente.
    fseek(arquivo, 0, SEEK_SET);
    fscanf(arquivo,"%d %d", &vertices, &arestas);

    //Releitura dos vertices
    Graph graph = cria_grafo(vertices_validos);

    for( aux = i = 0 ; i < vertices ; i++){
        fscanf(arquivo,"%d %d", &id, &idade);

        //Verificacao de quais pessoas tem idade < 35 e adicao ao grafo
        if( idade < 35 ){
            add_id_idade( graph, aux, id, idade);
            aux ++;
        }
    }


    //Receber o relacionamento entre as pessoas
    int id1, id2;
    int indx_id1, indx_id2;
    
    for ( i=0; i < arestas; i++){     
        fscanf(arquivo,"%d %d", &id1, &id2);
        
        // Verifica se id1 existe no grafo
        indx_id1 = verifica_id( graph, id1);
        if ( indx_id1 >= 0){
            
            // Verifica se id2 existe no grafo
            indx_id2 = verifica_id( graph, id2);
            if ( indx_id2 >= 0 && indx_id1 >= 0 ){

                add_aresta( graph, indx_id1, indx_id2); //Caso passe nas duas verificacoes, aresta e criada.
              
            }
        }
    }

    int primeira_pessoa;
    fscanf(arquivo,"%d", &primeira_pessoa);

    fclose(arquivo);

    int ponteiro[1];
    ponteiro[0] = 0;
    

    // Verifica se a primeira pessoa a ouvir existe no grafo. Se nao existir, ja retornar 0
    aux = verifica_id( graph, primeira_pessoa);

    if ( aux >= 0){
        conta_musica(graph, aux, ponteiro, -1);
        printf("%d", *ponteiro );
    }
    else{
        printf("0");
    }
    
    return 0;
    }


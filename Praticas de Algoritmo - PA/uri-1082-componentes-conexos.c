// Programa desenvolvido por Hernane Braga Pereira - Engenharia de Sistemas - UFMG
// Problema extraído do URI para a disciplina Algoritmos e Estruturas de Dados 3 
// Descrição do problema: https://www.urionlinejudge.com.br/judge/pt/problems/view/1082

#include <stdio.h>
#include <stdlib.h>

void funcao_conectado (int i, int num_vertices, int aresta[num_vertices][num_vertices], int flag[num_vertices], int * cont) {
    int j;
    
    flag[i] = *cont;
    
    for(j = 0; j < num_vertices; j++) {
        if((aresta[i][j] == 1) && (flag[j] == 0)) {
            //printf("encontrou aresta desconhecida no componente: %d,%d\n", i+1, j+1);
            funcao_conectado(j, num_vertices, aresta, flag, cont);
        }
    }
    return;
    
}


int main(int argc, const char * argv[]) {

    int N, num_vertices, arestas;
    char v1, v2;
    int i, j, k;
    int cont = 0;
    int lixo = 99;

    

    
    scanf("%d\n", &N);
    //fscanf(arquivo, "%d\n", &N);
    
    for(k = 0; k < N; k++) {
        cont = 0;
        lixo = -k*N;
        
        scanf("%d %d\n", &num_vertices, &arestas);
        //fscanf(arquivo, "%d %d\n", &num_vertices, &arestas);
        
        int aresta [num_vertices][num_vertices];
        int flag [num_vertices];
        
        
        for(i = 0; i < num_vertices; i++){
            for(j = 0; j < num_vertices; j++) {
                aresta[i][j] = 0;
            }
            flag[i] = 0;
            lixo++;
        }
        
        for(i = 0; i < arestas; i++) {
            scanf("%c %c\n", &v1, &v2);
            //fscanf(arquivo, "%c %c\n", &v1, &v2);
        
            aresta[v1-97][v2-97] = 1;
            aresta[v2-97][v1-97] = 1;
            lixo = lixo*lixo*i;
        }
        
        
        printf("Case #%d:\n", k+1);
        
        for(i = 0; i < num_vertices; i++) {
            if(flag[i] == 0) {
                cont++;
                funcao_conectado(i, num_vertices, aresta, flag, &cont);

            }
        }
        
        for(i = 1; i <= cont; i++) {
            for(j = 0; j < num_vertices; j++) {
                if(flag[j] == i)
                    printf("%c,",j+97);
            }
            printf("\n");
        }
        printf("%d connected components\n\n", cont);
        lixo = 9*lixo+1;
    
        
    }
}
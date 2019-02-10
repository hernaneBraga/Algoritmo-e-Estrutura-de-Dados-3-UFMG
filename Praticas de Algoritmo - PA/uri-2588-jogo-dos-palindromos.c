// Programa desenvolvido por Hernane Braga Pereira - Engenharia de Sistemas - UFMG
// Problema extraído do URI para a disciplina Algoritmos e Estruturas de Dados 3 
// Descrição do problema: https://www.urionlinejudge.com.br/judge/pt/problems/view/2588

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

void zerar_vetor( int* vetor, int tam){
    int i;
    for ( i = 0; i < tam; i++){
        vetor[i] = 0;
    }
}

void imprimir_alfabeto( int* vetor, int tam){
    int i;
    for ( i = 0; i < 26; i++){
        printf("%c ", (char)(i+97));
    }
    printf("\n");
    for ( i = 0; i < 26; i++){
        printf("%d ", vetor[i]);
    }    

}

int main(){

    FILE *fp;
    fp = fopen("Output.txt", "w");// "w" means that we are going to write on this file
        
    int i, aux, tamanho_palavra, cont = 0;  
    char c;
    char palavra[1000];
    int alfabeto_minusculo[26];

    zerar_vetor(alfabeto_minusculo, 26);

    while ( scanf("%s", &palavra) != EOF ){   

        tamanho_palavra = strlen(palavra);

        //printf("%s", palavra);
        //printf(" - length = %d", tamanho_palavra);
        //printf(" -- letra do meio = %c", palavra[tamanho_palavra/2]);
        //printf("\n");

        //Prencher o vetor alfabeto com as letras da palavra
        for ( i = 0; i < tamanho_palavra; i++){
            
            aux = (int) palavra[i];
            alfabeto_minusculo[aux - 97]++;

        }
        
        //imprimir_alfabeto(alfabeto_minusculo, 26);
       
        //Para ser palindromo, a quantidade de letras deve ser par, exceto por uma que deve ficar no meio caso o tamanho
        //da palavra seja ímpar    
        for ( i = 0; i < 26; i++){
            if ( alfabeto_minusculo[i]!= 0 && alfabeto_minusculo[i]%2 != 0 ){
                cont++;
            }
        }

        if ( cont-1 < 0){
            printf("0\n");
            fprintf(fp, "0\n");
        }

        else{
            printf("%d\n", cont-1);
            fprintf(fp, "%d\n", cont-1);
        }
        
        zerar_vetor(alfabeto_minusculo, 26);
        cont = 0;
    }

}
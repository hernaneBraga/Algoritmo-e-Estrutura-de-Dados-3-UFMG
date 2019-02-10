// Programa desenvolvido por Hernane Braga Pereira - Engenharia de Sistemas - UFMG
// Problema extraído do URI para a disciplina Algoritmos e Estruturas de Dados 3 
// Descrição do problema: https://www.urionlinejudge.com.br/judge/pt/problems/view/1234

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>


int main(){

    char c, aux;
    int cont = 0;


    while ( scanf("%c", &c) != EOF ){     

        if ( c != ' ' && c != '\n'){
           
           //Se for o primeiro da sequencia, deve ser MAIUSCULO
            if ( cont == 0){
                c = toupper(c);
                printf("%c", c); 
                cont ++;
                aux = c;
            }

            else if ( cont > 0 ){
                if ( isupper(aux)){
                    aux = tolower(c);
                    printf("%c", aux);
                    cont ++;
                }
                else {
                    aux = toupper(c);
                    printf("%c", aux);
                    cont ++;
                }      
            }
        }

        //Se pular de linha, é necessário reiniciar o contador
        else if ( c == '\n'){
            cont = 0;
            printf("\n");

        }

        else if ( c == ' '){
            printf("%c",c);
            //printf("1");
        }
        
        //Se for espaço em branco, ou outra coisa, só imprimir
        //else{
          //  printf("%c", c);
        //}

   }

}
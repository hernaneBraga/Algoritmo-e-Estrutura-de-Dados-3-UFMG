// Programa desenvolvido por Hernane Braga Pereira - Engenharia de Sistemas - UFMG
// Problema extraído do URI para a disciplina Algoritmos e Estruturas de Dados 3 
// Descrição do problema: https://www.urionlinejudge.com.br/judge/pt/problems/view/1088

// Referencia do algoritmo de count inversion merge: https://gist.github.com/henrya2/4679124

#include<stdio.h>
#include<stdlib.h>


/*
The maximum number of inversions that an
n-size array can have is 
    n*(n-1) / 2
*/

int count_inversion_merge(unsigned long int array[], int first, int last)
{
    int mid = (first+last)/2;
    int ai = first;
    int bi = mid+1;
    int final[last-first+1], finali=0;
    int inversion = 0, i;

    while (ai <= mid && bi <= last) {
        if (array[ai] <= array[bi]) {
                final[finali++] = array[ai++];
        } else {
                final[finali++] = array[bi++];
                inversion += mid - ai + 1;
        }
    }

    while (ai <= mid)
        final[finali++] = array[ai++];

    while (bi <= last) 
        final[finali++] = array[bi++];

    for (i=0 ; i<last-first+1 ; i++)
        array[i+first] = final[i];      

    return inversion;
}

int count_inversion(unsigned long int array[], int a, int b)
{
   
    int x, y, z, mid;
    if (a >= b) return 0;

    mid = (a+b)/2;
    
    x = count_inversion(array, a, mid);
    y = count_inversion(array, mid+1, b);
    z = count_inversion_merge(array, a, b);

    return x+y+z;
}

int main(){
    
    unsigned long int *vetor;
    vetor = malloc(1 * sizeof(unsigned long int));
    int len = -1;
    int i = 0;

    while(len != 0){
        scanf("%d", &len);
        if ( len == 0)
            break;

        vetor = realloc( vetor, len * sizeof(unsigned long int));
        for ( i = 0; i < len; i++){
            scanf("%ld", &vetor[i]);
        }

        int inversion = count_inversion(vetor, 0, len-1);
        if ( inversion % 2 == 0)
            printf("Carlos\n");
        else 
            printf("Marcelo\n");
    }

return 0;
}

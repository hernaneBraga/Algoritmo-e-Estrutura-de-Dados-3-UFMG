// =----------------------------------------------------------=
// =                           AVISO:                         =
// =                   MODIFIQUE ESTE ARQUIVO!                =
// = Aqui, você deve implementar, obrigatoriamente, essas     =
// = duas funções:                                            =
// =     - `a_menor_que_b`: deve retornar quando uma string   =
// =        é menor que a outra (ambos com o mesmo tamanho);  =
// =     - `external_sort`: aqui, você deverá implementar o   =
// =        seu trabalho. Ordene os registros em `input_file` =
// =        e escreva-os em `output_file`, usando somente     =
// =        `memory` KB de memória.                           =
// =                                                          =
// = Instruções:                                              =
// =     - use a função `mathias_malloc` ao invés de          =
// =       `malloc`;                                          =
// =     - use a função `mathias_free` ao invés de `free`;    =
// =     - lembre-se que você tem somente `memory` KB de      =
// =       memória;                                           =
// =     - note que a sua implementação de `a_menor_que_b`    =
// =       afetará o resultado da verificação da resposta.    =
// =                                                          =
// = Dicas:                                                   =
// =     - você pode usar a sua função `a_menor_que_b` em     =
// =       sua implementação da função `external_sort`;       =
// =                                                          =
// =                      BOM TRABALHO!                       =
// =----------------------------------------------------------=


// =----------------------------------------------------------=
// =----------------------------------------------------------=
// =----------------------------------------------------------=
// =----------------------------------------------------------=

/*  ALGORTIMOS E ESTRUTURAS DE DADOS 3 - TRABALHO PRATICO 1 
    HERNANE BRAGA PEREIRA - 2014112627 
    REFÊNCIAS UTILIZADAS:
    - Livro: Projeto de Algoritmos do autor Nivio Ziviani
    - Artigo sobre ordenação externa: https://en.wikipedia.org/wiki/External_sorting
    - Pseudo código de um merge sort externo: http://web.eecs.utk.edu/~leparker/Courses/CS302-Fall06/Notes/external-sorting2.html
    - Canal Programacao descomplicada: https://www.youtube.com/watch?v=sVGbj1zgvWQ
    - Canal Programação de Computadores: https://www.youtube.com/watch?v=BbeEfYID_dM
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "mem.h"

unsigned int len; //Numero de caracteres por linha do arquivo
unsigned int max_linhas; //Máximo de linhas que podem ser lidas no arquivo, dado uma memoria de entrada em Kb
int a_menor_que_b(char* a, char* b, int len);


// Estrutura para gerenciar buffers e arquivos temporários
struct arquivo{
    FILE *f;        // Arquivo que está sendo trabalhado no momento
    int pos, MAX;   // pos -> Posição atual dentro do arquivo. MAX -> Tamanho máximo de buffer
    char **buffer;  // Linha de caracteres que será escrita no arquivo 
};


/* Função de comparação do algoritmo qsort */ 
int compara(const void *a, const void *b) { 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
} 


// Parâmetros:
//     - nome: nome do arquivo
//     - vec: uma cadeia de caracteres de tamanho `len`;
//     - tam: tamanho  
//     - mudaLinhaFinal: flag para pular de linha (1) ou nao pular linha (0)
//     - primeira_vez: flag para escrever len no arquivo (1) ou nao escrever (0)
// Essa função salva a linha de caracteres em [vec] no arquivo de nome [nome]
void salvaArquivo(const char *nome, char** vec, int tam, int mudaLinhaFinal, int primeira_vez){
    int i;
    FILE *f = fopen(nome,"a");

    if ( primeira_vez == 1){
        fprintf(f,"%d\n", len);
    }
    
    for(i=0; i < tam-1; i++){
        fprintf(f,"%s\n", vec[i]);

    }
        
    if(mudaLinhaFinal == 0){
        fprintf(f,"%s", vec[tam-1]);

    }
        
    else{
        fprintf(f,"%s\n", vec[tam-1]);
    }
        
    fclose(f);
}


// Parâmetros:
//     - nome: nome do arquivo que será lido
// Esta função retorna o numero de arquivos temporários ordenados que foram criados, a partir do arquivo de entrada
int criaArquivosOrdenados(const char *nome){
    
    
    char novo[120];
    int i = 0, num_arquivos = 0, total = 0;


    FILE *f = fopen(nome,"r");
    fscanf(f, "%u%*c", &len); // Numero maximo de caracteres por linha de arquivo

    // Neste momento, max_linhas já possui seu valor em kb, vindo do parametro [memory] da funcao external_sort
    // Numero maximo de linhas que pode-se alocar e nao ocorrer estouro de memoria
    max_linhas = max_linhas / ( (len+1) * sizeof( char ) + sizeof( char** ));


    // Numero minimo de linhas que pode-se alocar e nao ocorrer estouro de memoria
    if ( max_linhas < 2)
        max_linhas = 2; 


    // Alocacao do vetor que lerá o arquivo de entrada, com tamanho baseado na restricao do usuario
    char** rec =  mathias_malloc( max_linhas * sizeof(char**));
    for ( i = 0; i < max_linhas ; i++){
         rec[i] = mathias_malloc( (len+1) * sizeof(char));
     }

    /* Leitura do arquivo de entrada */  
    while ( fscanf(f, "%[^\n]%*c", &rec[total][0]) != EOF) {        
        total++;
        
        // Quando o buffer estiver cheio, dados sao armazenados no arquivo temporario, ja ordenados
        if(total == max_linhas){

            num_arquivos++;
            sprintf(novo, "Temp%d.txt", num_arquivos);

            qsort(rec, total, sizeof(char *), compara);

            salvaArquivo(novo, rec, total, 0, 0);
            total = 0;
        }
    }

    // Caso algum dado tenha sobrado sem ser salvo em um arquivo, ele é salvo neste momento
    if(total > 0){
        num_arquivos++;
        sprintf(novo,"Temp%d.txt", num_arquivos);
        qsort(rec, total, sizeof(char *), compara);
        salvaArquivo(novo, rec, total, 0, 0);
    }
    
    fclose(f);


    //DESALOCAR O VETOR
    for ( i = 0; i < max_linhas; i++){   
        mathias_free(rec[i]);
    }
    mathias_free(rec);


    
    
    return num_arquivos;
}


// Parâmetros:
//     - arq: Estrutura de arquivo que preencherá o buffer
//     - tam_buffer: Tamanho do buffer
// Esta função preenche o buffer da estrutura arquivo, baseado no arquivo temporário ordenado já criado na função criarArquivosOrdenados
void preencheBuffer(struct arquivo* arq, int tam_buffer){
    int i;
    if(arq->f == NULL)
        return;

    arq->pos = 0;
    arq->MAX = 0;
    for(i=0; i < tam_buffer; i++){
        if(!feof(arq->f)){
            fscanf(arq->f,"%[^\n]%*c",&arq->buffer[arq->MAX][0]);   // Preenche o buffer do arquivo, de acordo com o número máximo de linhas do buffer
            arq->MAX++;
        }
        
        // Fecha-se o arquivo após preencher o buffer
        else{
            fclose(arq->f);
            arq->f = NULL;
            break;
        }
    }
}


// Parâmetros:
//     - arq: Estrutura de arquivo que preencherá o buffer
//     - tam_buffer: Tamanho do buffer
//     - num_arquivos: Número de arquivos temporários criados
//     - *menor: Linha de caracteres
// Esta função retorna (1) caso encontre o menor valor dentro de todos os arquivos temporários abertos abertos
int procuraMenor(struct arquivo* arq, int num_arquivos, int tam_buffer, char** menor, int qtdBuffer){
    int i, idx = -1;

    // Procura o menor valor dentro de todos os arquivos temporários abertos, começando pela posicao[0] de todos eles
    for(i=0; i < num_arquivos; i++){
        if(arq[i].pos < arq[i].MAX){
            if(idx == -1)
                idx = i;
            else{
                 if( a_menor_que_b( arq[i].buffer[arq[i].pos], arq[idx].buffer[arq[idx].pos], len) )
                idx = i;
            }
        }
    }

    // Caso tenha sido encontrado um menor valor, ele é salvo para ser gravado no arquivo final e atualiza-se a posicao atual do arquivo
    if(idx != -1){
        strcpy(menor[qtdBuffer], arq[idx].buffer[arq[idx].pos]);
        arq[idx].pos++;

        // Preenche buffer novamente, caso ele fique vazio
        if(arq[idx].pos == arq[idx].MAX)
            preencheBuffer(&arq[idx], tam_buffer);
        return 1;
    }else
        return 0;

}


// Parâmetros:
//     - nome_arq_final: Nome do arquivo de saida do programa, que ao final estará ordenado
//     - tam_buffer: Tamanho do buffer
//     - num_arquivos: Número de arquivos temporários criados
// Esta função gerencia os arquivos temporários criados e os junta em um arquivo final, ordenado
// utilizando a técnica de intercalação balanceadado merge sort externo
void merge(const char *nome_arq_final, int num_arquivos, int tam_buffer){
    char novo[120];
    
    int i, j;

    // Buffer que será escrito no arquivo final
    char** buffer = mathias_malloc( tam_buffer * sizeof(char**));
    for ( i = 0; i < tam_buffer ; i++){
        buffer[i] = mathias_malloc( (len+1) * sizeof(char));
    }

    // Criacao da estrutura arquivo
    struct arquivo* arq;
    arq = (struct arquivo*)malloc(num_arquivos * sizeof(struct arquivo));
    for(i=0; i < num_arquivos; i++){
        sprintf(novo,"Temp%d.txt",i+1);
        arq[i].f = fopen(novo,"r");
        arq[i].MAX = 0;
        arq[i].pos = 0;
        
        arq[i].buffer = malloc( tam_buffer * sizeof(char**));
        for ( j = 0; j < tam_buffer ; j++){
            arq[i].buffer[j] = malloc( (len+1) * sizeof(char));
        }

        preencheBuffer(&arq[i], tam_buffer);
    }



    int primeira_vez = 0;
    int qtdBuffer = 0; 


    // Procura o menor elemento dentro de todos os arquivos temporários abertos e o salva no arquivo final qunado buffer estiver cheio
    while(procuraMenor(arq, num_arquivos, tam_buffer, buffer, qtdBuffer) == 1){
       
        qtdBuffer++;

        if(qtdBuffer == tam_buffer){

            if ( primeira_vez == 0){
                salvaArquivo(nome_arq_final, buffer, tam_buffer, 1, 1);
                primeira_vez++;
                qtdBuffer = 0;
            }
            else{
                salvaArquivo(nome_arq_final, buffer, tam_buffer, 1, 0);
                qtdBuffer = 0;
            }
            
        }
    }

    // Caso tenha sobrado algum valor no buffer que não foi salvo no arquivo final, ele é salvo neste momento.
    if(qtdBuffer != 0){
        if ( primeira_vez == 0 ){
                salvaArquivo(nome_arq_final, buffer, qtdBuffer, 1, 1);
        }
        else
            salvaArquivo(nome_arq_final, buffer, qtdBuffer, 1, 0);
    }



    // Desalocando a estrutura de arquivo 
    for(i=0; i < num_arquivos; i++)
        free(arq[i].buffer);
    free(arq);



    // Desalocando os buffers
    for (i = 0; i < tam_buffer; i++)
        mathias_free(buffer[i]);
        
    mathias_free(buffer);

}


// Parâmetros:
//     - a: uma cadeia de caracteres de tamanho `len`;
//     - b: uma cadeia de caracteres de tamanho `len`;
//     - len: o tamanho (quantidade de bytes) de `a` e `b`.
// Essa função deve retornar 1, se `a` é menor que `b` (`a` deve vir antes de `b` no
// arquivo), e 0 caso contrário.
// Ela também é usada para verificação da ordenação! Então, se você implementá-la
// erroneamente, a verificação também estará errada! 
int a_menor_que_b(char* a, char* b, int len) {
    //Compara duas strings através de cada letra
    int i;
    for ( i = 0 ; i < len ; i++){
        if ( b[i] <  a[i]){
            return 0;
        }

        else if ( b[i] > a[i]){    
            return 1;
        }

        else{

        }
    }
    return 1;
}


// Parâmetros:
//     - input_file: o nome do arquivo com os registros de entrada;
//     - output_file: o nome do arquivo com os registros de entrada ordenados;
//     - memory: o limite de memória a ser usado.
// Essa função deverá ler todos registros do arquivo `input_file`, ordená-los e
// escrevê-los em `output_file`, usando memória menor ou igual a `memory`. Lembre-se
// de fechar todos os arquivos que você usar por aqui!!
void external_sort(const char* input_file, const char* output_file, unsigned int memory) {

    max_linhas = (memory * 1024); // Converte o numero na entrada para Kb

    char novo[120]; // Nome dos arquivos temporários que serão criados
    int num_arquivos = criaArquivosOrdenados(input_file); // Numero de arquivos ordenados gerados



    int i; 

    // Tamanho maximo que o buffer pode possuir, sendo pelo menos = 2
    int tam_buffer = max_linhas / (num_arquivos + 1); 
    if ( tam_buffer <= 0 )
        tam_buffer = 2;



    // Une os arquivos temporarios em um unico arquivo de saida ordenado
    merge(output_file, num_arquivos, tam_buffer); 

    // Apaga os arquivos temporarios criados
    for(i=0; i < num_arquivos; i++){
        sprintf(novo,"Temp%d.txt",i+1);
        remove(novo);
    }

}

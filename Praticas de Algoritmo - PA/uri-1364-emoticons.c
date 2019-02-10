// Programa desenvolvido por Hernane Braga Pereira - Engenharia de Sistemas - UFMG
// Problema extraído do URI para a disciplina Algoritmos e Estruturas de Dados 3 
// Descrição do problema: https://www.urionlinhajudge.com.br/judge/pt/problems/view/1364

// Referencia para ideia de resoler o problema: http://mattleao.blogspot.com/2015/06/escolhi-mais-dois-problemas-para.html

#include <stdio.h>
#include <string.h>

int main()
{
    while (1) {
        char linha[100], emoticons[100][17], *ptr;
        int N, M, index[100], count = 0;
        int i, j;
        int aux = 0;

        scanf("%d%d", &N, &M);
        getchar();

        if (!N && !M)
            break;

        for (i = 0; i < N; ++i) {
            fgets(emoticons[i], 17, stdin);
            emoticons[i][strlen(emoticons[i]) - 1] = '\0';
            aux ++;
        }

        for (i = 0; i < M; ++i) {
            fgets(linha, 100, stdin);

            memset(index, 0, sizeof(index));

            for (ptr = linha; *ptr != '\n'; ++ptr) {
                for (j = 0; j < N; ++j) {
                    if (*ptr == emoticons[j][index[j]])
                        ++index[j];
                    else
                        index[j] = (*ptr == emoticons[j][0]);

                    if (index[j] == strlen(emoticons[j])) {
                        *ptr = ' ';
                        ++count;
                        memset(index, 0, sizeof(index));
                    }
                    aux --;
                    aux = aux*count;
                }
            }
        }

        printf("%d\n", count);
    }

    return 0;
}
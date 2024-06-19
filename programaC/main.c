// Código redigido por
// Catarina Moreira Lima nUsp 8957221
// Eduarda Almeida Garrett de Carvalho nUsp 14566794

#include <stdio.h>
#include "funcionalidades.h"
#include "cabecalho.h"
#include "funcoes_fornecidas.h"
#include "lista.h"
#include "registros.h"
#include "indice.h"

int main()
{

    char comando;                   // comando para função 1-6
    char nomeCSV[50], arqDados[50]; // nome arquivo em CSV, nome arquivo em binário
    char nomeIndice[50];            // nome arquivo de índice
    int nroBuscas;                  // número de buscas a serem feitas na função 3

    scanf("%c ", &comando); // lê qual comando será executado
                 // Consume newline character to avoid issues

    switch (comando)
    {
    case '1':
        scanf("%s %s", nomeCSV, arqDados);
        func1(nomeCSV, arqDados);
        break;
    case '2':
        scanf("%s", arqDados);
        func2(arqDados);
        break;
    case '3':
        scanf("%s %d", arqDados, &nroBuscas);
        func3(arqDados, nroBuscas);
        break;
    case '4':
 
        scanf("%s %s", arqDados, nomeIndice);
        func4(arqDados, nomeIndice);
        // funcionalidade fornecida
        binarioNaTela(nomeIndice);
        break;
    case '5':
        scanf("%s %s %d", arqDados, nomeIndice, &nroBuscas);
        func5(arqDados, nomeIndice, nroBuscas);
        break;
    case '6':
        scanf("%s %s %d", arqDados, nomeIndice, &nroBuscas);
        func6(arqDados, nomeIndice, nroBuscas);
        break;
    case '9':
        printf("entrei na 9\n");
        fflush(stdout);

        registroIndice *index = NULL;
        registroIndice r1, r2, r3;

        r1.byteoffset = 2;
        r1.id = 0;
        r2.byteoffset = 7;
        r2.id = 1;
        r3.byteoffset = 60;
        r3.id = 2;

        insereIndice(&index, r1, 0);
        insereIndice(&index, r2, 1);
        insereIndice(&index, r3, 2);

        for (int i = 0; i < 3; i++)
        {
            printf("id: %d / bo: %ld\n", index[i].id, index[i].byteoffset);
        }

        removeIndice(&index, r2.id, 3);

        for (int i = 0; i < 2; i++)
        {
            printf("id: %d / bo: %ld\n", index[i].id, index[i].byteoffset);
        }

        free(index);
        break;

    default:
        break;
    }

    return 0;
}
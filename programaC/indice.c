#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indice.h"
#include "binario.h"

/// @brief Esceve, no começo do arquivo de indice, o seu status
/// @param f Ponteiro responsável pela manipulação do aquivo de indice
/// @param c Ponteiro para buffer de cabeçalho do indice
void escreveCabIndice(FILE *f, cabecalhoIndice *c)
{
    // posiciona ponteiro no início do arquivo de indice
    fseek(f, 0, SEEK_SET);
    // escreve status do arquivo no cabeçalho c
    fwrite(&c->status, sizeof(char), 1, f);
}

/// @brief Lê, no começo do arquivo de indice, o seu status
/// @param f Ponteiro responsável pela manipulação do aquivo de indice
/// @param c Ponteiro para buffer de cabeçalho do indice
void leCabecalhoIndice(FILE *f, cabecalhoIndice *c)
{
    // inicializa valores base no cabeçalho c
    inicializaCabecalhoIndice(c);
    // posiciona para o inicio do arquivo
    fseek(f, 0, SEEK_SET);
    // lê dado no arquivo de indice
    fread(&c->status, sizeof(char), 1, f);
}

/// @brief Inicializa o status com valor default
/// @param c Ponteiro para buffer de cabeçalho do indice
void inicializaCabecalhoIndice(cabecalhoIndice *c)
{
    c->status = '0';
}

/// @brief Algoritmo Quick Sort para ordenação de vetor
/// @param v vetor de registros do indice
/// @param f primeiro id do vetor
/// @param l último elemento do vetor
static void quick(registroIndice *v, int f, int l)
{

    if (f >= l)
        return;

    int m = (l + f) / 2;
    int pivot = v[m].id;
    int i = f;
    int j = l;

    while (1)
    {
        while (v[i].id < pivot)
            i++;

        while (v[j].id > pivot)
            j--;

        if (i >= j)
            break;

        registroIndice aux = v[i];
        v[i] = v[j];
        v[j] = aux;

        i++;
        j--;
    }

    quick(v, f, j);
    quick(v, j + 1, l);
}

/// @brief Ordena, pelo id, vetor que armazena todos os registros de um certo indice
/// @param v vetor com todos os registros
/// @param tam tamanho do vetor com os registros; quantidade existente de registros no indice
void sort_indice(registroIndice *v, int tam)
{
    quick(v, 0, tam - 1);
}

/// @brief Escreve campo a campo todos os registros no arquivo de indice
/// @param f Ponteiro do arquivo de indice
/// @param v Vetor que contém todos os registros a serem escritos
/// @param tam Tamanho do vetor de registros; quantidade de registros a serem escritos

void escreveIndice(FILE *f, registroIndice **v, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        //printf("escrevendo id: %d bo: %ld no bo %ld\n", (*v)[i].id, (*v)[i].byteoffset, ftell(f));
        fwrite(&((*v)[i].id), sizeof(int), 1, f);          // escreve id
        fwrite(&((*v)[i].byteoffset), sizeof(long), 1, f); // escreve byteoffset
    }
    free(*v);
}



/// @brief carrega um indice do arquivo de dados para memoria
/// @param f_ind ponteiro para o arquivo
/// @param n numero de registros
/// @return vetor dinamico
registroIndice *carregaIndice(FILE *f_ind, int n)
{
    // retorna o vetor de indice
    registroIndice *vet;

    vet = (registroIndice *)malloc(n * sizeof(registroIndice));

    for (int i = 0; i < n; i++)
    {
        fread(&vet[i].id, sizeof(int), 1, f_ind);
        fread(&vet[i].byteoffset, sizeof(long), 1, f_ind);
    }

    //printf("o ultimo carregado eh id: %d bo: %ld", vet[n-1].id, vet[n-1].byteoffset);
    return vet;
}


/// @brief funcao que insere um novo registro no indice de forma ordenada
/// @param vet indice dinamico
/// @param r registro a ser inserido
/// @param n tamanho 
void insereIndice(registroIndice **vet, registroIndice r, int n) {
    int i;
    //realloc para tamanho maior
    *vet = (registroIndice *)realloc(*vet, (n + 1) * sizeof(registroIndice));
    if (*vet == NULL) {
        printf("erro alocacao\n");
        return;
    }

    (*vet)[n].byteoffset = 0;
    (*vet)[n].id = 0;
    

    // Acha a posicao para inserir ordenado
    for (i = n - 1; (i >= 0 && (*vet)[i].id > r.id); i--) {
        (*vet)[i + 1] = (*vet)[i]; // Shift nos elementos para abrir espaco
    }

    // Insere o novo registro
    (*vet)[i + 1] = r;

}

/// @brief funcao que remove um registro do indice
/// @param vet indice
/// @param id id a ser removido
/// @param n tamanho
void removeIndice(registroIndice **vet, int id, int n) {
    int i;

  
    for (i = 0; i < n; i++) {
        if ((*vet)[i].id == id) {
            // Shift para apagar se encontrar o id
            for (int j = i; j < n; j++) {
               
                (*vet)[j] = (*vet)[j + 1];
            }
            *vet = (registroIndice *)realloc(*vet, (n) * sizeof(registroIndice));

            return;
        }
    }
}



/// @brief destroi indice existente
/// @param indice indice a ser destruido
void destroiIndice(char *indice)
{
    // abre como escrita e escreve inconsistente
    cabecalhoIndice c;
    FILE *f_ind;

    c.status = '0';

    abreArquivoBinario(&f_ind, indice, "wb");
    fwrite(&c, sizeof(cabecalhoIndice), 1, f_ind);
    fclose(f_ind);
}



/// @brief realiza busca binaria no indice
/// @param vet vetor a ser buscado
/// @param inicio inivio
/// @param fim fim
/// @param chave chave
/// @return -1 se nao acha, o byte offset se acha
long buscaBinaria(registroIndice *vet, int inicio, int fim, int chave)
{
    int left = inicio;
    int right = fim;

    while (left <= right)
    {
        int meio = left + (right - left) / 2; // Calcula o índice do meio

        if (vet[meio].id == chave) // Se o ID no meio corresponde ao ID buscado
            return vet[meio].byteoffset; // Retorna o byte offset do registro
        if (vet[meio].id < chave) // Se o ID no meio é menor que o ID buscado
            left = meio + 1; // Move o índice do início para a direita
        else
            right = meio - 1; // Move o índice do final para a esquerda
    }

    return -1; // Retorna -1 se o ID não for encontrado
}
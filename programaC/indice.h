#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INDICE_H
#define INDICE_H

#define TEM_CAB_INDICE 1 // status = 1 byte
#define TAM_REG_INDICE 12 // id = 4 bytes; byteoffset = 8 bytes;

typedef struct {
    char status;        // '0' se inconsistente, '1' se consistente
}cabecalhoIndice;

typedef struct {
    int id;             // id do jogador indentificado
    long byteoffset;    // endereço do primeiro byte do registro no arquivo de dados
}registroIndice;

void escreveCabIndice(FILE *f, cabecalhoIndice *c);
void leCabecalhoIndice(FILE *f, cabecalhoIndice *c);
void inicializaCabecalhoIndice(cabecalhoIndice *c);
void sort_indice(registroIndice *v, int tam);
void escreveIndice(FILE *f, registroIndice **v, int tam);
long buscaBinaria(registroIndice *vet, int inicio, int fim, int chave);
void reescreveIndice(registroIndice *vet, FILE *f_ind, int n);
void destroiIndice(char *indice);
void removeIndice(registroIndice **vet, int id, int n);
void insereIndice(registroIndice **vet, registroIndice r, int n);
registroIndice *carregaIndice(FILE *f_ind, int n);
int criaIndice(char *nomeArq);

#endif

#ifndef REGISTROS_H
#define REGISTROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"
#include "indice.h"
#include "lista.h"


#define TAM_FIXO 6*sizeof(int) + sizeof(long) + sizeof(char)


/// @brief Define a struct para o registro de acordo com as especificações
typedef struct{
    char removido;
    int tamanhoRegistro;
    long Prox;
    int id;
    int idade;
    int tamNomeJog;
    char *nomeJogador;
    int tamNacionalidade;
    char *nacionalidade;
    int tamNomeClube;
    char *nomeClube;
}registro;

//prototipagem das funções
void escreveRegistroArquivo(FILE *f, registro *r);
int leRegistroArquivo(FILE *f, registro *r);
void liberaRegistro(registro *r);
void inicializaRegistro(registro *r);
void imprimeRegistro(registro r);
void buscaSequencial (char campos[][20], char strs[][20], int *intrs, FILE *f, int qntd);
int tamReal(registro r);
void remocaoSequencial (char campos[][20], char strs[][20], int *intrs, FILE *f_dados, registroIndice *vet, int qntd, cabecalho *c, t_lista *removidos);
void removeLogicamente(registro *r, cabecalho *c, FILE *f_dados, registroIndice *vet, t_lista *removidos, long ByteOffset);
void remocaoID(registroIndice *vet, FILE *f_dados, char campos[][20], char strs[][20], int *intrs, int qntd, cabecalho *c, t_lista *removidos);
void carregaRemOrd(t_lista *removidos, FILE *f);
void reescreveRemovidos(FILE *f, t_lista *removidos);
void carregaRemovidos(t_lista *removidos, FILE *f);
void reutilizaEspaco(FILE *f_dados, long parada);
void novoRegistro(registro *r, registroIndice *ri);
void insereFinalArq(FILE* f_dados, registro *r, cabecalho *c, registroIndice **vet, registroIndice *ri);


#endif
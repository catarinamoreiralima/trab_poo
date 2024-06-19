#ifndef CABECALHO_H
#define CABECALHO_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define TAM_CAB 25

typedef struct{
    char status; // marca se é consistente 
    long topo; 
    long proxByteOffset; // ponteiro para próximo byte offser
    int nroRegArq; // quantidade registros não removidos
    int nroRegRem;  // quantidade registros removidos
}cabecalho;


void escreveCabecalho(FILE *f, cabecalho *c);
void leCabecalho(FILE *f, cabecalho *c);
void pulaCabecalho(FILE *f);
void inicializaCabecalho(cabecalho *c);








#endif
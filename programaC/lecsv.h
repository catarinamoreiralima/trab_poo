#ifndef LECSV_H
#define LECSV_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "registros.h"
#include "lecsv.h"

//"id" "idade" "nomeJogador" "nacionalidade" "nomeClube"
#define TAMANHO_TITULO_CSV 45

FILE *AbreArqCSV (FILE **f, char *nomeArq);
int leRegistroCSV (FILE *f, registro *r);
void pulaTitulos(FILE *f);


#endif
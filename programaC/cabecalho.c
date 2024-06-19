#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "cabecalho.h"

/// @brief Função que inicializa o cabeçalho com valores default
/// @param c Cabeçalho a ser inicializado
void inicializaCabecalho(cabecalho *c){
    //inicializa como inconscistente
    c->status = '0';
    //topo como -1
    c->topo = -1;
    //contadores zerados
    c->nroRegRem = 0;
    c->nroRegArq = 0;
}

/// @brief Função que escreve o cabeçalho no arquivo binario
/// @param f ponteiro para o arquivo
/// @param c cabeçalho a ser escrito
void escreveCabecalho(FILE *f, cabecalho *c){
    //posiciona o ponteiro do arquivo no inicio
    fseek(f, 0, SEEK_SET);
    //escreve o cabecalho
    fwrite(&c->status, sizeof(char), 1, f);
    fwrite(&c->topo, sizeof(long), 1, f);
    fwrite(&c->proxByteOffset, sizeof(long), 1, f);
    fwrite(&c->nroRegArq, sizeof(int), 1, f);
    fwrite(&c->nroRegRem, sizeof(int), 1, f);

}

/// @brief Le o cabeçalho do arquivo
/// @param f ponteiro do arquivo
/// @param c cabeçalho a receber a leitura
void leCabecalho(FILE *f, cabecalho *c){

    inicializaCabecalho(c);
    //posiciona o ponteiro no inicio do arquivo
    fseek(f, 0, SEEK_SET);
    
    fread(&c->status, sizeof(char), 1, f);

    fread(&c->topo, sizeof(long), 1, f);

    fread(&c->proxByteOffset, sizeof(long), 1, f);

    fread(&c->nroRegArq, sizeof(int), 1, f);

    fread(&c->nroRegRem, sizeof(int), 1, f);

}

/// @brief função que pula o tamanho do cabeçalho
/// @param f ponteiro pro arquivo
void pulaCabecalho(FILE *f){
    fseek(f, TAM_CAB, SEEK_SET);
}

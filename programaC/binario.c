#include <stdio.h>
#include <string.h>

#include "binario.h"

/// @brief Abre um arquivo binario no modo passado
/// @param f ponteiro pro arquivo
/// @param nome nome do arquivo
/// @return 
int abreArquivoBinario(FILE **f, char *nome, char *modo){
    (*f) = fopen(nome, modo);
    if ((*f) == NULL){
        printf("Falha no processamento do arquivo na abertura do %s.\n", nome);
        //se nao conseguir abrir, ja fecha o programa
        return -1;
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "registros.h"
#include "lecsv.h"

/// @brief Pula  leitura de "id", "idade", "nomeJogador", "nacionalidade" e "nomeClube" do csv
/// @param f Ponteiro do arquivo csv
void pulaTitulos(FILE *f){
    fseek(f, TAMANHO_TITULO_CSV, SEEK_SET);
}


/// @brief abre arquivo csv para leitura
/// @param f Ponteiro do arquivo csv    
/// @param nomeArq Nome do arquivo csv
/// @return retorna 0 para sucesso 
FILE *AbreArqCSV (FILE **f, char *nomeArq){
    // abre o arquivo com o nome atribuido nos parâmetros
    *f = fopen(nomeArq, "r");

    // retorna mensagem de erro, caso não dê para abrir arquivo
    if(*f == NULL){
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    // 0 para sucesso
    return 0; 
}

/// @brief funcao que le campo variavel do csv
/// @param str string tamanho variavel
/// @param tam tamanho da string
/// @param f ponteiro para arquivo
/// @return 0 - sucesso, 1 - falha
static int pegaCampoVariavel(char **str, int *tam, FILE *f){
    char aux[100];
    //verifica se ocorreu leitura valida, até a vírgula ou '\n'
    if(fscanf(f, "%[^,\n]", aux)>1){
        //se sim, copia para o registro
        *tam = strlen(aux);
        *str = (char *) malloc(sizeof(char)*((*tam)+1));
        if(*str == NULL){
            printf("erro de alocação dinamica\n");
            return 1;
        }
        strcpy(*str, aux);
        return 0;
    }
    //senao, tam = 0;

    *tam = 0;
    return 0;

}


/// @brief Verifica se há um registro a ser lido, se sim, lê e armazena em cada respectivo campo
/// @param f Ponteiro para arquivo csv
/// @param r Struct que contem cada campo do registro
/// @return Retorna 1 se existe um registrador a ser lido, 0 cc
int leRegistroCSV(FILE *f, registro *r){
    
    //char auxiliar para consumir as virgulas
    char c;

    //inicializa o registro com infos default
    inicializaRegistro(r);

    //verifica se teve leitura valida id: sempre existe e tem pelo menos 1 char
    if(fscanf(f, "%d", &r->id)>0){
        //consome virgula
        c=fgetc(f);

        //pega campo idade
        if(fscanf(f, "%d", &r->idade) == 0){
            // se não há o dado, preenche com -1
            r->idade = -1;
        }

        //consome virgula
        c=fgetc(f);

        //pega campo nome e tamNome
        pegaCampoVariavel(&r->nomeJogador, &r->tamNomeJog, f);
        
        //consome virgula
        c=fgetc(f);
        
        
        //pega campo nacionalidade e tamNacionalidade
        pegaCampoVariavel(&r->nacionalidade, &r->tamNacionalidade, f);
        
        //consome virgula
        c=fgetc(f);
        
        
        //pega campo clube e tamClube
        pegaCampoVariavel(&r->nomeClube, &r->tamNomeClube, f);

        //salva tamanho do registro
        r->tamanhoRegistro = (r->tamNacionalidade + r->tamNomeClube + r->tamNomeJog + TAM_FIXO);

        return 1;
    }
    return 0;
}

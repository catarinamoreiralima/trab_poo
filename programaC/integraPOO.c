#include "integraPOO.h"


void helloWorld(char *s)
{
    //printf("hello world\n");
    printf("%s\n", s);
}

void printNumber(int n){
    printf("%d\n", n);
}

int returnAddition(int a, int b){
    return a + b;
}

typedef struct busca{
    int id; // -1 indica não usado
    int idade; // -1 indica não usado
    char *nomejogador;
    char *nac;
    char *nomeclube;
} busca_t;

/**
 * Parses a string into a busca_t structure.
 *
 * @param string The string to be parsed.
 * @return The parsed busca_t structure.
 *
 * @throws None
 */
busca_t parseBusca(char *string){
    busca_t Teste;

    char *token = string;
    char delCampo[] = "|";

    // parse id
    token = strtok(token, delCampo);
    //printf("%s\n", token);

    if (strcmp(token, "@") == 0){  // verifica se campo foi utilizado na busca
        Teste.id = -1;
    }else{ //transforma o token em inteiro
        Teste.id = atoi(token);
    }
    
    
    // parse idade
    token = strtok(NULL, delCampo);
    //printf("%s\n", token);
    
    if (strcmp(token, "@") == 0){ // verifica se campo foi utilizado na busca
        Teste.idade = -1;
    }else{ //transforma o token em inteiro
        Teste.idade = atoi(token);
    }

    // parse nomejogador
    token = strtok(NULL, delCampo);
    //printf("%s\n", token);
    Teste.nomejogador = token;

    // parse nacionalidade
    token = strtok(NULL, delCampo);
    //printf("%s\n", token);
    Teste.nac = token;

    // parse nomeclube
    token = strtok(NULL, delCampo);
    //printf("%s\n", token);
    Teste.nomeclube = token;

    //printf("%d %d %s %s %s\n", Teste.id, Teste.idade, Teste.nomejogador, Teste.nac, Teste.nomeclube);

    return Teste;
}

// Prints the elements of the busca_t struct B: id, idade, nomejogador, nac, and nomeclube.
void printBusca(busca_t B){
    printf("%d %d %s %s %s\n", B.id, B.idade, B.nomejogador, B.nac, B.nomeclube);
}

// Cria um array de strings com os campos utilizados na busca
void criaCampos(busca_t B){
    char *campos[20];

    int cont = 0;

    // para cada campo, verifica se foi usado na busca
    // se sim, adiciona na lista de campos
    if (B.id != -1){
        campos[cont] = "id";
        cont++;
    }
    if(B.idade != -1){
        campos[cont] = "idade";
        cont++;
    }
    if(strcmp(B.nomejogador, "@") != 0){
        campos[cont] = "nomeJogador";
        cont++;
    }
    if(strcmp(B.nac, "@") != 0){
        campos[cont] = "nacionalidade";
        cont++;
    }
    if(strcmp(B.nomeclube, "@") != 0){
        campos[cont] = "nomeClube";
        cont++;
    }

    // teste
    // for (int i = 0; i < cont; i++){
    //     printf("%s\n", campos[i]);
    // }

}

typedef struct vetorCampos{
    char **campos;
    int *camposi;
} vetorCampos_t;

void printVetorCampos(vetorCampos_t par){

}

vetorCampos_t criaCamposValor(busca_t B){
    vetorCampos_t par;
    
    char *campos[20];
    int camposi[20];
    
    int cont = 0;


    if (B.id != -1){
        camposi[cont] = B.id;
        cont++;
    }
    if(B.idade != -1){
        camposi[cont] = B.idade;
        cont++;
    }
    if(strcmp(B.nomejogador, "@") != 0){
        campos[cont] = B.nomejogador;
        cont++;
    }
    if(strcmp(B.nac, "@") != 0){
        campos[cont] = B.nac;
        cont++;
    }
    if(strcmp(B.nomeclube, "@") != 0){
        campos[cont] = B.nomeclube;
        cont++;
    }

    // // teste
    // for (int i = 0; i < cont; i++){
    //     if (campos[i] != NULL) printf("%s\n", campos[i]);
    //     if (camposi[i] != NU) printf("%d\n", camposi[i]);
    // }

    par.campos = campos;
    par.camposi = camposi;


    return par;
}


// Recebe uma string contendo os campos de uma busca, e printa os elementos da busca
void buscaHandler(char *camposBusca){

    char buscaTeste[] = "@|12|marcos|@|palmeiras$asbdj";
    char delRegistro[] = "$";
    char delCampo[] = "|";

    busca_t Teste;
    
    char *token, *str;
    str = camposBusca;

    // parse um registro
    token = strtok(str, delRegistro);
    printf("%s\n", token);

    // faz a struct de busca a partir da string do registro
    Teste = parseBusca(token); 

    printBusca(Teste);

    criaCampos(Teste);

    // TODO: tá dando problema ao integrar a busca q recebe na função de busca sequencial
    // por causa da lógica de leitura dos campos, mas acho que resolve mudando a logica
    // da string recebida

    //vetorCampos_t par = criaCamposValor(Teste);
    
    //printVetorCampos(par);

    //criaCamposValor(Teste);
}


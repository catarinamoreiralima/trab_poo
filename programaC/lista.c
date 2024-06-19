#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "indice.h"

/// @brief funcao que inicializa uma lista ligada
/// @param l lista
/// @return sucessor/falha
int inicializar(t_lista *l)
{

    l->primeiro = NULL;
    l->ultimo = NULL;
    return SUCESSO;
}

/// @brief busca posicao de uma chave especifica
/// @param chave chave a ser buscada
/// @param l lista
/// @return ponteiro para posicao
static t_apontador pesquisar_pos(long chave, t_lista *l)
{

    t_apontador p = l->primeiro;

    while (p != NULL)
    {
        // achou o elemento?
        if (p->elemento.tamanho == chave)
            return p;

        p = p->proximo;
    }

    return p;
}

/// @brief funcao que busca uma chave em uma lista
/// @param chave chave buscada
/// @param l lista
/// @return elemento que eh daquela chave
t_elemento pesquisar(long chave, t_lista *l)
{

    t_apontador p = pesquisar_pos(chave, l);

    if (p == NULL)
    {
        printf("Deu ruim, nao achou!\n");

        t_elemento e;
        e.tamanho = -1;

        return e;
    }
    else
    {
        return p->elemento;
    }
}

/// @brief funcao que insere um elemento na cabeca de uma lista
/// @param e elemento a ser inserido
/// @param l lista
/// @return sucesso/fracasso
int inserirPrimeiro(t_elemento e, t_lista *l)
{ // primeira pos



    t_apontador p = (t_apontador)malloc(sizeof(t_no));

    if (p == NULL)
    {
        printf("Lista (memoria) cheia!\n");
        return CHEIA;
    }

    //insere sempre no inicio

    p->elemento = e;

    p->proximo = l->primeiro;
    l->primeiro = p;


    return SUCESSO;
}

/// @brief funcao que insere de forma ordenada em uma lista
/// @param e elemento a ser inserido
/// @param l lista
/// @return sucesso/fracasso
int inserirOrdenado(t_elemento e, t_lista *l)
{
    t_apontador p = (t_apontador)malloc(sizeof(t_no));

    if (p == NULL)
    {
        printf("Lista (memoria) cheia!\n");
        return CHEIA;
    }

    p->elemento = e;

    //se a lista estiver vazia ou se for inserir na primeira posicao
    if (l->primeiro == NULL || l->primeiro->elemento.tamanho > e.tamanho)
    {
        p->proximo = l->primeiro;
        l->primeiro = p;
        return SUCESSO;
    }

    //procura local correto de inserir
    t_apontador aux = l->primeiro;
    while (aux->proximo != NULL && aux->proximo->elemento.tamanho <= e.tamanho)
    {
        aux = aux->proximo;
    }

    p->proximo = aux->proximo;
    aux->proximo = p;

    return SUCESSO;
}





/// @brief funcao que inserel elemento na cauda de uma lista
/// @param e elemento a ser inserido
/// @param l lista
/// @return sucesso/fracasso
int inserirUltimo(t_elemento e, t_lista *l)
{ // primeira pos

    t_apontador p = (t_apontador)malloc(sizeof(t_no));

    if (p == NULL)
    {
        printf("Lista (memoria) cheia!\n");
        return CHEIA;
    }

    t_apontador aux = l->ultimo;

    p->elemento = e;
    p->proximo = NULL;

    if (l->primeiro == NULL)
    {
        
        l->primeiro = p;
        l->ultimo = p;
        return SUCESSO;

    }

    l->ultimo->proximo = p;
    l->ultimo = p;
    
    return SUCESSO;
}

/// @brief funcao que remove um elemento de uma lista
/// @param chave chave a ser removida
/// @param l lista
/// @return sucesso/fracasso
int remover(long chave, t_lista *l)
{

   // printf("removendo o bo: %ld\n", chave);
    if (vazia(l))
    {
        printf("Nao achei para remover\n");
        return NAO_EXISTE;
    }

    t_apontador p = l->primeiro;
    t_apontador p2; // aux

    if (p->elemento.byteOffset == chave)
    { // chave na primeira pos

        p2 = l->primeiro;
        l->primeiro = p2->proximo;

        free(p2);

        return SUCESSO;
    }

    while (p->proximo != NULL)
    {

        if (p->proximo->elemento.byteOffset == chave)
        {

            //printf("achei pra remover\n");
            p2 = p->proximo;
            p->proximo = p2->proximo;

            free(p2);

            return SUCESSO;
        }

        p = p->proximo;
    }

   // printf("Nao achei para remover\n");
    return NAO_EXISTE;
}

/// @brief verifica se uma lista esta vazia
/// @param l lista
/// @return 1 - vazia / 0 - nao vazia
int vazia(t_lista *l)
{

    if (l->primeiro == NULL)
        return 1;

    return 0;
}



/// @brief Retorna o byteoffset do registro logicamente removido, utilizando a lógica Best Fit
/// @param tamNovo tamanho do registro a ser inserido
/// @param l lista com os registros removidos
long achaTamanho(t_lista *l, int tamNovo)
{
    t_apontador candidato = l->primeiro;
    t_apontador melhorCandidato = NULL;

    while (candidato != NULL)
    {
        if (candidato->elemento.tamanho >= tamNovo)
        {
            if (melhorCandidato == NULL || candidato->elemento.tamanho < melhorCandidato->elemento.tamanho)
            {
                melhorCandidato = candidato;
            }
        }
        candidato = candidato->proximo;
    }

    if (melhorCandidato != NULL)
    {
        return melhorCandidato->elemento.byteOffset;
    }
    else
    {
        return -1;
    }
}



/// @brief libera memoria alocada
/// @param t lista
void liberaLista(t_lista *t){

    t_apontador aux1 = t->primeiro;
    t_apontador aux = NULL;

    while(aux1 != NULL){
        aux = aux1;
        aux1 = aux->proximo;
        free(aux);
    }
        
}

/// @brief imprime elementos de uma lista
/// @param l lista
void imprimeLista (t_lista *l){
    t_apontador p = l->primeiro;

    while (p != NULL){
        printf("bo: %ld // tamanho: %d\n", p->elemento.byteOffset, p->elemento.tamanho);
        p = p->proximo;
    }
}
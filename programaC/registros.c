#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "registros.h"
#include "lecsv.h"
#include "cabecalho.h"
#include "indice.h"
#include "lista.h"
#include "funcoes_fornecidas.h"

/// @brief Escreve um registro em um arquivo binário
/// @param f Ponteiro para arquivo
/// @param r Registro a ser escrito
void escreveRegistroArquivo(FILE *f, registro *r)
{

    // escreve campo a campo
    fwrite(&r->removido, sizeof(char), 1, f);

    fwrite(&r->tamanhoRegistro, sizeof(int), 1, f);

    fwrite(&r->Prox, sizeof(long), 1, f);

    fwrite(&r->id, sizeof(int), 1, f);

    fwrite(&r->idade, sizeof(int), 1, f);

    fwrite(&r->tamNomeJog, sizeof(int), 1, f);

    if (r->tamNomeJog > 0)
    {
        fwrite(r->nomeJogador, r->tamNomeJog * sizeof(char), 1, f);
    }

    fwrite(&r->tamNacionalidade, sizeof(int), 1, f);

    if (r->tamNacionalidade > 0)
    {
        fwrite(r->nacionalidade, r->tamNacionalidade * sizeof(char), 1, f);
    }

    fwrite(&r->tamNomeClube, sizeof(int), 1, f);

    if (r->tamNomeClube > 0)
    {
        fwrite(r->nomeClube, r->tamNomeClube * sizeof(char), 1, f);
    }

    liberaRegistro(&(*r));
}

/// @brief Le um registro de um arquivo.
/// @param f Ponteiro do arquivo binário
/// @param r Registro a receber a leitura
/// @return Retorna 1 (true) se consegue ler e 0 (false) se não consegue
int leRegistroArquivo(FILE *f, registro *r)
{
    inicializaRegistro(r);
    // verifica se consegue ler o primeiro byte -> ou seja, se existe registro
    if (fread(&r->removido, sizeof(char), 1, f) > 0)
    {
        // le demais campos
        fread(&r->tamanhoRegistro, sizeof(int), 1, f);
        fread(&r->Prox, sizeof(long), 1, f);
        fread(&r->id, sizeof(int), 1, f);
        if ((*r).id == 0)
        {
            return 0;
        }
        fread(&r->idade, sizeof(int), 1, f);
        fread(&r->tamNomeJog, sizeof(int), 1, f);

        // aloca espaço para a string
        if (r->tamNomeJog > 0)
        {
            r->nomeJogador = malloc((r->tamNomeJog + 1) * sizeof(char));
            fread(r->nomeJogador, r->tamNomeJog * sizeof(char), 1, f);
            // adiciona \0 para utilização em memoria primaria
            r->nomeJogador[r->tamNomeJog] = '\0';
        }

        fread(&r->tamNacionalidade, sizeof(int), 1, f);
        if (r->tamNacionalidade > 0)
        {
            r->nacionalidade = malloc((r->tamNacionalidade + 1) * sizeof(char));
            fread(r->nacionalidade, r->tamNacionalidade * sizeof(char), 1, f);
            r->nacionalidade[r->tamNacionalidade] = '\0';
        }

        fread(&r->tamNomeClube, sizeof(int), 1, f);
        if (r->tamNomeClube > 0)
        {
            r->nomeClube = malloc((r->tamNomeClube + 1) * sizeof(char));
            fread(r->nomeClube, r->tamNomeClube * sizeof(char), 1, f);
            r->nomeClube[r->tamNomeClube] = '\0';
        }

        return 1;
    }

    return 0;
}

/// @brief libera memoria alocada de registro
/// @param r registro cuja memoria precisa ser liberada
void liberaRegistro(registro *r)
{
    if (r->nacionalidade != NULL || r->tamNacionalidade != 0)
    {
        free(r->nacionalidade);
    }
    if (r->nomeClube != NULL || r->tamNomeClube != 0)
    {
        free(r->nomeClube);
    }
    if (r->nomeJogador != NULL || r->tamNomeJog != 0)
    {
        free(r->nomeJogador);
    }
}

/// @brief inicializa registro com valores default
/// @param r registro a ser inicializado
void inicializaRegistro(registro *r)
{
    r->id = -1;
    r->idade = -1;
    r->nacionalidade = NULL;
    r->nomeClube = NULL;
    r->nomeJogador = NULL;
    r->Prox = -1;
    r->removido = '0';
    r->tamanhoRegistro = 0;
    r->tamNacionalidade = 0;
    r->tamNomeClube = 0;
    r->tamNomeJog = 0;
}

/// @brief imprime registro na tela conforme especificações
/// @param r registro a ser impresso
void imprimeRegistro(registro r)
{
    printf("ID do Jogador: %d\n", r.id);

    printf("Idade do Jogador: %d\n", r.idade);
    
    // imprime preambulo
    printf("Nome do Jogador: ");
    if (r.tamNomeJog > 0) // verifica se há esse dado
        printf("%s\n", r.nomeJogador);
    else
        printf("SEM DADO\n");

    printf("Nacionalidade do Jogador: ");
    if (r.tamNacionalidade > 0) // verifica se há esse dado
        printf("%s\n", r.nacionalidade);
    else
        printf("SEM DADO\n");

    printf("Clube do Jogador: ");
    if (r.tamNomeClube > 0) // verifica se há esse dado
        printf("%s\n", r.nomeClube);
    else
        printf("SEM DADO\n");

    printf("\n");
}

char* imprimeRegistroStream(registro r)
{
    char *resposta;
    size_t size;
    FILE *stream;
    stream = open_memstream(&resposta, &size);

    fprintf(stream, "ID do Jogador: %d\n", r.id);

    fprintf(stream, "Idade do Jogador: %d\n", r.idade);
    
    // imprime preambulo
    fprintf(stream, "Nome do Jogador: ");
    if (r.tamNomeJog > 0) // verifica se há esse dado
        fprintf(stream,"%s\n", r.nomeJogador);
    else
        fprintf(stream,"SEM DADO\n");



    fprintf(stream, "Nacionalidade do Jogador: ");
    if (r.tamNacionalidade > 0) // verifica se há esse dado
        fprintf(stream, "%s\n", r.nacionalidade);
    else
        fprintf(stream, "SEM DADO\n");



    fprintf(stream,"Clube do Jogador: ");
    if (r.tamNomeClube > 0) // verifica se há esse dado
        fprintf(stream,"%s\n", r.nomeClube);
    else
        fprintf(stream,"SEM DADO\n");


    //fprintf(stream,"\n");

    fclose(stream);
    
    return resposta;

}


/**
 * Performs a sequential search in a file to find records that match the given
 * fields and values. Prints the records that match all the fields. If the
 * "id" field is specified, the function stops after finding the first match.
 *
 * @param campos An array of strings representing the fields to search for.
 * @param strs An array of strings representing the values to search for.
 * @param intrs An array of integers representing the values to search for.
 * @param f The file to search in.
 * @param qntd The number of fields to search for.
 *
 * @throws None.
 */
void buscaSequencial(char campos[][20], char strs[][20], int *intrs, FILE *f, int qntd)
{

    char eh_id, bate;
    int cont;
    registro r;
    char *resposta;
    cont = 0;

    eh_id = 0;
    // verifica registro a registro se bate todos os campos e se sim, imprime
    while (leRegistroArquivo(f, &r))
    {

        FILE *aux = f;
        int tam_reg = r.tamanhoRegistro;

        // tudo bate ate q se prove o contrario
        bate = 1;
    

        for (int j = 0; j < qntd; j++) // para cada campo
        {

            // se estiver removido, nao bate
            if (r.removido == '1')
            {
                bate = 0;
                break;
            }

            if (strcmp(campos[j], "id") == 0) // se o campo j é id
            {
                eh_id = 1;
                if (r.id != intrs[j]) // se o id NAO é o mesmo
                {
                    bate = 0; // nao bate
                    break; // sai fora
                }
            }
            if (strcmp(campos[j], "idade") == 0) //se o campo j é idade
                if (r.idade != intrs[j]) // se a idade NAO eh a mesma
                {
                    bate = 0;
                    break;
                }

            if (strcmp(campos[j], "nacionalidade") == 0)
            {
                // verifica tamanho -> erro no strcmp para string inexistente
                if (r.tamNacionalidade == 0)
                {
                    bate = 0;
                    break;
                }
                if (strcmp(r.nacionalidade, strs[j]))
                {
                    bate = 0;
                    break;
                }
            }

            if (strcmp(campos[j], "nomeJogador") == 0)
            {
                // verifica tamanho -> erro no strcmp para string inexistente
                if (r.tamNomeJog == 0)
                {
                    bate = 0;
                    break;
                }
                if (strcmp(r.nomeJogador, strs[j]))
                {
                    bate = 0;
                    break;
                }
            }
            if (strcmp(campos[j], "nomeClube") == 0)
            {
                // verifica tamanho -> erro no strcmp para string inexistente
                if (r.tamNomeClube == 0)
                {
                    bate = 0;
                    break;
                }

                if (strcmp(r.nomeClube, strs[j]))
                {
                    bate = 0;
                    break;
                }
            }
        }

   
        // se nenhum campo nao bateu, imprime e aumenta contador
        if (bate)
        {
            // abre um file para agir como uma stream, read and write
            resposta = imprimeRegistroStream(r);
            printf("%s", resposta);


            cont++;
            if (eh_id)
            {
                // libera alocacao
                liberaRegistro(&r);
                break;
            }
        }

        // libera alocacao
        liberaRegistro(&r);


    }

    // se nao encontrou nenhum registro, imprime mensagem de erro
    if (cont == 0)
    {
        sprintf(resposta, "Registro inexistente.\n\n");
        printf("%s", resposta);

        return;
    }
}

char * buscaSequencialPOO(char campos[][20], char strs[][20], int *intrs, FILE *f, int qntd)
{

    char eh_id, bate;
    int cont;
    registro r;

    cont = 0;

    char *resposta;
    size_t size;
    FILE *stream;

    stream = open_memstream(&resposta, &size);

    eh_id = 0;

    char *buf;
    // verifica registro a registro se bate todos os campos e se sim, imprime
    while (leRegistroArquivo(f, &r))
    {

        FILE *aux = f;
        int tam_reg = r.tamanhoRegistro;

        // tudo bate ate q se prove o contrario
        bate = 1;
    

        for (int j = 0; j < qntd; j++) // para cada campo
        {

            // se estiver removido, nao bate
            if (r.removido == '1')
            {
                bate = 0;
                break;
            }

            if (strcmp(campos[j], "id") == 0) // se o campo j é id
            {
                eh_id = 1;
                if (r.id != intrs[j]) // se o id NAO é o mesmo
                {
                    bate = 0; // nao bate
                    break; // sai fora
                }
            }
            if (strcmp(campos[j], "idade") == 0) //se o campo j é idade
                if (r.idade != intrs[j]) // se a idade NAO eh a mesma
                {
                    bate = 0;
                    break;
                }

            if (strcmp(campos[j], "nacionalidade") == 0)
            {
                // verifica tamanho -> erro no strcmp para string inexistente
                if (r.tamNacionalidade == 0)
                {
                    bate = 0;
                    break;
                }
                if (strcmp(r.nacionalidade, strs[j]))
                {
                    bate = 0;
                    break;
                }
            }

            if (strcmp(campos[j], "nomeJogador") == 0)
            {
                // verifica tamanho -> erro no strcmp para string inexistente
                if (r.tamNomeJog == 0)
                {
                    bate = 0;
                    break;
                }
                if (strcmp(r.nomeJogador, strs[j]))
                {
                    bate = 0;
                    break;
                }
            }
            if (strcmp(campos[j], "nomeClube") == 0)
            {
                // verifica tamanho -> erro no strcmp para string inexistente
                if (r.tamNomeClube == 0)
                {
                    bate = 0;
                    break;
                }

                if (strcmp(r.nomeClube, strs[j]))
                {
                    bate = 0;
                    break;
                }
            }
        }

   
        // se nenhum campo nao bateu, imprime e aumenta contador
        if (bate)
        {
            // abre um file para agir como uma stream, read and write

            buf = imprimeRegistroStream(r);
            fprintf(stream, "%s \n", buf);
            //printf("%s", resposta);


            cont++;
            if (eh_id)
            {
                // libera alocacao
                liberaRegistro(&r);
                break;
            }
        }

        // libera alocacao
        liberaRegistro(&r);


    }

    fclose(stream);
    // se nao encontrou nenhum registro, imprime mensagem de erro
    if (cont == 0)
    {
        return "Registro inexistente.";

        
    }

    return resposta;
}

/// @brief funcao que verifica o tamanho das informacoes validas de um registro
/// @param r registro
/// @return tamanho real do registro
int tamReal(registro r)
{
    return TAM_FIXO + r.tamNacionalidade + r.tamNomeClube + r.tamNomeJog;
}

/// @brief Funcao que remove registros que nao tem como campo de busca o ID
/// @param campos quais os campos a serem buscados
/// @param strs campos string
/// @param intrs campos inteiros
/// @param f_dados arquivo de dados
/// @param f_ind arquivo de indice
/// @param qntd quantos campos na remocao
/// @param c cabecalho
void remocaoSequencial(char campos[][20], char strs[][20], int *intrs, FILE *f_dados, registroIndice *vet, int qntd, cabecalho *c, t_lista *removidos, t_lista *removidos_ordenado)
{

    char bate;
    registro r;
    long byteOffsetAtual;


    // verifica registro a registro se bate todos os campos e se sim, remove
    while (1)
    {
        byteOffsetAtual = ftell(f_dados);

        if (!leRegistroArquivo(f_dados, &r))
            break;

        // tudo bate ate q se prove o contrario
        bate = 1;

        for (int i = 0; i < qntd; i++)
        {

            // se estiver removido, nao bate
            if (r.removido == '1')
            {
                bate = 0;
                break;
            }

            if (strcmp(campos[i], "idade") == 0)
                if (r.idade != intrs[i])
                {
                    bate = 0;
                    break;
                }

            if (strcmp(campos[i], "nacionalidade") == 0)
            {

                // verifica tamanho -> erro no strcmp para string inexistente
                if (r.tamNacionalidade == 0)
                {
                    bate = 0;
                    break;
                }
                if (strcmp(r.nacionalidade, strs[i]) != 0)
                {
                    bate = 0;
                    break;
                }
            }

            if (strcmp(campos[i], "nomeJogador") == 0)
            {

                // verifica tamanho -> erro no strcmp para string inexistente
                if (r.tamNomeJog == 0)
                {
                    bate = 0;
                    break;
                }

                if (strcmp(r.nomeJogador, strs[i]) != 0)
                {
                    bate = 0;
                    break;
                }
            }
            if (strcmp(campos[i], "nomeClube") == 0)
            {

                // verifica tamanho -> erro no strcmp para string inexistente
                if (r.tamNomeClube == 0)
                {
                    bate = 0;
                    break;
                }

                if (strcmp(r.nomeClube, strs[i]) != 0)
                {
                    bate = 0;
                    break;
                }
            }
        }
        // se nenhum campo nao bateu, imprime e aumenta contador -> aqui ja garante que ele nao estava removido antes e evita acesso desnecessario
        if (bate)
        {           
            removeLogicamente(&r, c, f_dados, vet, removidos, removidos_ordenado, byteOffsetAtual);

        }


        // libera alocacao
        liberaRegistro(&r);

        if ((ftell(f_dados) - r.tamanhoRegistro) != byteOffsetAtual)
        {
            // corrige caso tenha reaproveitamento de espaco
            fseek(f_dados, byteOffsetAtual + r.tamanhoRegistro, SEEK_SET);
        }
    }

 
}

/// @brief Função que remove um registro pela chave primaria ID
/// @param vet indice dinamico
/// @param f_dados ponteiro pro arquivo de dados
/// @param campos campos a serem utilizados para comparacao
/// @param strs correspondencia em string
/// @param intrs correspondencia de inteiros
/// @param qntd quantidade de campos
/// @param c cabecalho do arquivo de dados
/// @param removidos lista dinamica dos registros removidos
void remocaoID(registroIndice *vet, FILE *f_dados, char campos[][20], char strs[][20], int *intrs, int qntd, cabecalho *c, t_lista *removidos, t_lista *removidos_ordenado)
{

    long byteOffsteAtual = -1;
    registro r;
    int bate;


    //  itera por quandos campos tiverem
    for (int i = 0; i < qntd; i++)
    {
        // busca qual campo é o id
        if (strcmp(campos[i], "id") == 0)
        {
            // pega o byteOffset do indice dinamico
            byteOffsteAtual = buscaBinaria(vet, 0, (*c).nroRegArq - 1, intrs[i]);
        
        }
    }
    // se for -1 nao esta no indice
    if (byteOffsteAtual == -1)
    {
        return;
    }

    // posiciona o ponteirp de arquivo no registro em questao
    fseek(f_dados, byteOffsteAtual, SEEK_SET);
    // le o registro
    leRegistroArquivo(f_dados, &r);

   

    // se ja nao estiver removido, remove
    if (r.removido != '1')
        removeLogicamente(&r, c, f_dados, vet, removidos, removidos_ordenado, byteOffsteAtual);

    liberaRegistro(&r);
}

/// @brief Remove um arquivo logicamente + remove indice
/// @param r registro a ser removido
/// @param c cabecalho arquivo de dados
/// @param f_dados ponteiro pra arquivo de dados
/// @param vet indice dinamico
/// @param removidos lista dinamica removidos
void removeLogicamente(registro *r, cabecalho *c, FILE *f_dados, registroIndice *indice_dinamico, t_lista *removidos, t_lista *removidos_ordenado, long byteOffset)
{

    t_elemento e_lista; // buffer p insercao lista removidos


    // aumenta n de regs removidos do cabecalho
    (*c).nroRegRem++;
    // diminui o numero de arq armazenados
    (*c).nroRegArq--;

    
    // remove do indice
    removeIndice(&indice_dinamico, (*r).id, (*c).nroRegArq);
    // pega o byteoffset to primeiro byte do registro -> ponteiro vai estar apontando p byte apos registro
    e_lista.byteOffset = byteOffset;
    // tamanho do registro
    e_lista.tamanho = r->tamanhoRegistro;
    // insere na lista de removidos
    inserirPrimeiro(e_lista, removidos);
    inserirOrdenado(e_lista, removidos_ordenado);
}

/// @brief funcao que carrega o byteOffsets e tamanhos dos registros removidos de um arquivo de dados em uma lista ligada
/// @param removidos lista de removidos
/// @param f ponteiro arquivo de dados
void carregaRemovidos(t_lista *removidos, FILE *f_dados)
{
    registro reg;
    t_elemento e;
    cabecalho c;
    long byteOffsetAtual;

    fseek(f_dados, 0, SEEK_SET);
    leCabecalho(f_dados, &c);

    if (c.topo != -1)
    {
        fseek(f_dados, c.topo, SEEK_SET);

        do
        {
            byteOffsetAtual = ftell(f_dados);

            // Verifica se ainda há registros a serem lidos
            if (!leRegistroArquivo(f_dados, &reg))
                break;

            e.byteOffset = byteOffsetAtual;
            e.tamanho = reg.tamanhoRegistro;
            inserirUltimo(e, removidos);

            fseek(f_dados, reg.Prox, SEEK_SET);

            liberaRegistro(&reg);

        } while (reg.Prox != -1);
    }
}

/// @brief funcao que carrega os registros removidos de um arquivo de dados de forma ordenada inversamente por tamanho
/// @param removidos lista de removidos
/// @param f ponteiro arquivo de dados
void carregaRemOrd(t_lista *removidos, FILE *f)
{
    registro r;
    t_elemento e;
    cabecalho c;
    long proximo;

    fseek(f, 0, SEEK_SET);
    leCabecalho(f, &c);
    if (c.topo != -1)
    {
        proximo = c.topo;
        while (proximo != -1)
        {
            fseek(f, proximo, SEEK_SET);
            leRegistroArquivo(f, &r);
            e.byteOffset = proximo;
            e.tamanho = r.tamanhoRegistro;
            inserirOrdenado(e, removidos);
            proximo = r.Prox;
            liberaRegistro(&r);
        }
    }
}

/// @brief funcao que reescreve os arquivos removidos em um arquivo de dados
/// @param f ponteiro para arquivo de dados
/// @param removidos lista de removidos
void reescreveRemovidos(FILE *f, t_lista *removidos)
{
    t_apontador proximo;
    char rem = '1';
    long fim = -1;

    // se a lista esta vazia n faz nada
    if (removidos->primeiro != NULL)
    {
        // inicia na cabeca da lista
        proximo = removidos->primeiro;
        // o primeiro ja sei q nao eh null -> teste if
        while (proximo->proximo != NULL)
        {
            // posiciona no byte inicial do registro removido
            fseek(f, proximo->elemento.byteOffset, SEEK_SET);
            // marca como removido
            fwrite(&rem, sizeof(char), 1, f);
            // reescreve tamanho do registro
            fwrite(&proximo->elemento.tamanho, sizeof(int), 1, f);
            // reescreve o proximo
            fwrite(&proximo->proximo->elemento.byteOffset, sizeof(long), 1, f);
            // vai pro proximo registro
            proximo = proximo->proximo;
        }

        // no ultimo, o prox eh -1 // tbm abarca se so tiver 1
        fseek(f, proximo->elemento.byteOffset, SEEK_SET);
        fwrite(&rem, sizeof(char), 1, f);
        fwrite(&proximo->elemento.tamanho, sizeof(int), 1, f);
        fwrite(&fim, sizeof(long), 1, f);
    }
}

/// @brief funcao que insere lixo ate um certo byte offset
/// @param f_dados ponteiro pro arquivo
/// @param parada ponto de parada
void reutilizaEspaco(FILE *f_dados, long parada)
{
    char lixo = '$';

    while (ftell(f_dados) < parada)
    {
        fwrite(&lixo, sizeof(char), 1, f_dados);
    }
}

/// @brief funcao que le informcoes de um novo registro de dados do teclado
/// @param r registro de dados
/// @param ri registro de indice
void novoRegistro(registro *r, registroIndice *ri)
{

    char testeNulo[50]; // buffer testa se há o dado a ser inserido no campo

    // inserção do ID
    scanf("%d", &(*r).id);
    (*ri).id = (*r).id; // já coloca no buffer de registrador do indice

    // inserção IDADE
    scanf("%s", testeNulo);
    //  verifica se há o dado de idade
    if (strlen(testeNulo) == 0 || strcmp("NULO", testeNulo) == 0)
    {
        (*r).idade = -1;
    }
    else
    { // se tiver idade
        (*r).idade = atoi(testeNulo);
    }

    getchar();
    // inserção NOME DO JOGADOR
    scan_quote_string(testeNulo);
    // printf("%s\n", testeNulo);
    //  verifica se há o dado de nome
    if (strlen(testeNulo) == 0 || ("NULO", testeNulo) == 0)
    {
        (*r).tamNomeJog = 0;
        (*r).nomeJogador = NULL;
    }
    else
    {
        // se tiver dado do nome
        (*r).tamNomeJog = strlen(testeNulo);
        (*r).nomeJogador = (char *)malloc(sizeof(char) * ((*r).tamNomeJog + 1));
        strncpy((*r).nomeJogador, testeNulo, (*r).tamNomeJog + 1);
    }
    getchar();
    // inserção NACIONALIDADE
    scan_quote_string(testeNulo);

    //  verifica se há o dado de nome
    if (strlen(testeNulo) == 0 || ("NULO", testeNulo) == 0)
    {
        (*r).tamNacionalidade = 0;
        (*r).nacionalidade = NULL;
    }
    else
    {
        // se tiver dado da nacionalidade
        (*r).tamNacionalidade = strlen(testeNulo);
        (*r).nacionalidade = (char *)malloc(sizeof(char) * ((*r).tamNacionalidade + 1));
        strncpy((*r).nacionalidade, testeNulo, (*r).tamNacionalidade + 1);
    }
    getchar();
    // inserção NOME DO CLUBE
    scan_quote_string(testeNulo);
    
    //  verifica se há o dado de nome
    if (strlen(testeNulo) == 0 || ("NULO", testeNulo) == 0)
    {
        (*r).tamNomeClube = 0;
        (*r).nomeClube = NULL;
    }
    else
    {
        // se tiver dado da nacionalidade
        (*r).tamNomeClube = strlen(testeNulo);
        (*r).nomeClube = (char *)malloc(sizeof(char) * ((*r).tamNomeClube + 1));
        strncpy((*r).nomeClube, testeNulo, (*r).tamNomeClube + 1);
    }

    // seta os demais campos
    (*r).removido = '0';
    (*r).Prox = -1;

    // tamanho será inserido demependendo do modo de inserção
}

/// @brief funcao que inserev um registro no final do arquivo e arruma o respectivo registro de indice
/// @param f_dados ponteiro para o arquivo de dados
/// @param r registro a ser inserido no arquivo
/// @param c cabecalho arquivo de dados
/// @param vet indice dinamico
/// @param ri registro de indice
void insereFinalArq(FILE* f_dados, registro *r, cabecalho *c, registroIndice **vet, registroIndice *ri)
{
    (*r).tamanhoRegistro = tamReal(*r);
    // posiciona no prox byte livre
    fseek(f_dados, (*c).proxByteOffset, SEEK_SET);
    (*ri).byteoffset = (*c).proxByteOffset;
    //  insere sequencial
    escreveRegistroArquivo(f_dados, &(*r));
    insereIndice(&(*vet), (*ri), (*c).nroRegArq);
    (*c).proxByteOffset = ftell(f_dados);
}


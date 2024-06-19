#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "registros.h"
#include "lecsv.h"
#include "cabecalho.h"
#include "funcionalidades.h"
#include "binario.h"
#include "funcoes_fornecidas.h"
#include "indice.h"
#include "lista.h"

/// @brief Lê um arquivo CSV e escreve seu conteúdo no formato de registros em um arquivo binário
/// @param nomecsv Nome do arquivo csv
/// @param arqDados Nome do arquivo binario
/// @return 1 - falha 0 - sucesso
int func1(char *nomecsv, char *arqDados)
{
    // declara ponteiros dos arquivos e demais necessarios
    FILE *fcsv;
    FILE *fbin;
    registro r;
    cabecalho c;

    // Abre o arquivo CSV
    AbreArqCSV(&fcsv, nomecsv);

    // Abre o arquivo binário no modo de escrita
    abreArquivoBinario(&fbin, arqDados, "wb");

    // inicializa cabeçalho
    inicializaCabecalho(&c);

    // pula os titulos csv
    pulaTitulos(fcsv);

    // escreve cabecalho -> se cair o inconsistente ta escrito
    escreveCabecalho(fbin, &c);

    // Enquanto consegue ler um registro, escreve no binário
    while (leRegistroCSV(fcsv, &r))
    {
        // incrementa numero de registradores
        c.nroRegArq++;
        escreveRegistroArquivo(fbin, &r);
    }

    // atualiza o cabeçalho
    c.status = '1';
    c.proxByteOffset = ftell(fbin);

    // escreve o cabeçalho no inicio
    escreveCabecalho(fbin, &c);

    // fecha os arquivos
    fclose(fcsv);
    fclose(fbin);

    // binario na tela
    binarioNaTela(arqDados);
}

/// @brief lê o arquivo binário e escreve, nome, nacionalidade e clube do jogadores não deletados
/// @param arqDados nome do arquivo em binário a ser lido
int func2(char *arqDados)
{

    FILE *fbin;
    registro r;
    cabecalho c;

    // Abre arquivo binário para leitura
    abreArquivoBinario(&fbin, arqDados, "rb");

    // lê as infos do cabeçalho, ajustando também o ponteiro de leitura
    leCabecalho(fbin, &c);

    // verifica se está consistente
    if (c.status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    // verifica se existem registros
    if (c.nroRegArq == 0)
    {
        printf("Registro inexistente.\n\n");
        exit(0);
    }

    // enquanto existe resistro a ser lido
    while (leRegistroArquivo(fbin, &r))
    {

        // verifica se registro não foi removido
        if (r.removido == '0')
        {
            imprimeRegistro(r);
        }

        // corrige posicao caso registro tenha reutilizado espaço
        fseek(fbin, r.tamanhoRegistro - tamReal(r), SEEK_CUR);
    }

    // ao final, fecha o arquivo
    fclose(fbin);
}

/// @brief Retorna n buscas
/// @param arqDados nome do arquivo binario a ser lido
/// @param n quantidade de buscas
int func3(char *arqDados, int buscas)
{
    FILE *f;
    cabecalho c;
    int qntd;            // quantidade de campos para filtrar a pesquisa
    char campos[20][20]; // lista de campos para pesquisa
    char strs[20][20];
    int intrs[20];
    int eh_id;

    // abre arquivo em modo leitura
    abreArquivoBinario(&f, arqDados, "rb");

    leCabecalho(f, &c);
    if (c.status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        return 1;
    }

    for (int i = 0; i < buscas; i++)
    {

        // le quantos campos serao utilizados na pesquisa
        scanf("%d", &qntd);

        // pega os campos
        for (int j = 0; j < qntd; j++)
        {
            scanf("%s", campos[j]);
            // verifica se o campo eh int ou string
            if (strcmp(campos[j], "idade") == 0 || strcmp(campos[j], "id") == 0)
                scanf("%d", &intrs[j]);
            else
                scan_quote_string(strs[j]);
        }

        // IMPRIME QUAL A BUSCA
        printf("Busca %d\n\n", i + 1);

        // volta ao primeiro registro
        fseek(f, 0, SEEK_SET);

        pulaCabecalho(f);

        buscaSequencial(campos, strs, intrs, f, qntd);
    }

    fclose(f);
}

/// @brief Cria um arquivo de indice com base em um arquivo de dados existente
/// @param arqDados Nome do arquivo de dados
/// @param indice Nome do arquivo de índice
/// @return 1 para sucesso e 0 para falha

int func4(char *arqDados, char *indice)
{
    FILE *f_ind;                       // ponteiro para arquivo indice
    FILE *f_dados;                      // ponteiro para arquivo de dados
    cabecalhoIndice c_ind;                 // buffer do cabeçalho indice
    cabecalho c_dados;                  // buffer do cabeçalho do arquivo r
    registroIndice *indice_dinamico = NULL; // vetor de registros do indice
    registro r_dados;                   // buffer para resistros do arquivo de dados
    registroIndice r_indice;             //registro de indice           


    // abre arquivo de dados: leitura
    abreArquivoBinario(&f_dados, arqDados, "rb");

    // le cabeçalho arquivo dados
    leCabecalho(f_dados, &c_dados);

    // se não houver registros logicamente não removidos, encerra a função
    if (c_dados.status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(f_dados);
        exit(0);
    }

    // se não houver registros logicamente não removidos, encerra a função
    if (c_dados.nroRegArq == 0)
    {
        fclose(f_dados);
        exit(0);
    }

    // abre arquivo indice: escrita
    abreArquivoBinario(&f_ind, indice, "wb");

    // status = '0' do indice
    inicializaCabecalhoIndice(&c_ind);

    // já escreve o cabeçalho como inconscistente; define posição correta do ponteiro
    escreveCabIndice(f_ind, &c_ind);

    // alocação de memória para cada registro a ser escrito no indice
    indice_dinamico = (registroIndice *)malloc(sizeof(registroIndice) * c_dados.nroRegArq);

    int i = 0;             // contador para atribuição dos registros no vetor
    pulaCabecalho(f_dados); // coloca o ponteiro do arquivo de dados logo após o cabeçalho do arquivo

    while (1)
    {
        long posicaoAtual = ftell(f_dados);

        if (!leRegistroArquivo(f_dados, &r_dados))
        {
            break;
        }

        r_indice.byteoffset = posicaoAtual;
        r_indice.id = r_dados.id;


        // se o registro não estiver logicamente removido, insira no vetor
        if (r_dados.removido != '1')
        {
           indice_dinamico[i] = r_indice;
           i++;
        }

        if (ftell(f_dados) != (posicaoAtual + r_dados.tamanhoRegistro))
        {
            fseek(f_dados, (posicaoAtual + r_dados.tamanhoRegistro), SEEK_SET);
        }

        liberaRegistro(&r_dados);
    }

    // ordena os registros pelos id's
    sort_indice(indice_dinamico, c_dados.nroRegArq);

    // escreve, de forma ordenada, os registros no arquivo de indice
    escreveIndice(f_ind, &indice_dinamico, c_dados.nroRegArq);

    // terminou a escrita do índice, atualiza status no arquivo
    c_ind.status = '1';
    escreveCabIndice(f_ind, &c_ind);

    // fecha e salva arquivos abertos
    fclose(f_ind);
    fclose(f_dados);
}

/// @brief Funcionalidade que realiza n remocoes
/// @param arqDados nome do arquivo de dados
/// @param indice nome do arquivo de indice
/// @param n numero de remocoes
void func5(char *arqDados, char *indice, int n)
{

    FILE *f_dados, *f_ind; // ponteiros responsáveis por manipular arquivo de dados e de índice
    cabecalho c_dados;     // buffer de cabeçalho de dados
    cabecalhoIndice c_ind; // buffer de cabeçalho de índice
    int qntd;              // quantidade de campos para filtrar a remocao
    char campos[20][20];   // lista de campos para remocao
    char strs[20][20];     // campos string
    int intrs[20];         // campos int
    int eh_id;             // verifica se é id
    registroIndice *indice_dinamico;   // vetor que armazena todos os registros contidos no índice
    t_lista removidos;     // lista que contém todos os registros removidos no arquivo de dados

    // abre arquivo de dados em modo leitura e escrita
    abreArquivoBinario(&f_dados, arqDados, "r+b");

    // le cabecalho arquivo de dados
    leCabecalho(f_dados, &c_dados);

    // verifica se arquivo de dados está conscistente
    if (c_dados.status == '0')
    {
        printf("Falha no processamento do arquivo por causa do status.\n");
        exit(0);
    }

    // se nao existem registros nao logicamente removidos, fecha
    if (c_dados.nroRegArq == 0)
    {
        // nao tem nada pra remover
        fclose(f_dados);
        exit(0);
    }

    // verifica se ja existe um arquivo de indice
    f_ind = fopen(indice, "rb");
    // se nao tem, cria um

    if (f_ind == NULL)
    {
        func4(arqDados, indice);
        // como a funcionalidade 4 fecha o arquivo, abrimos novamente
        f_ind = fopen(indice, "r+b");
    }

    // le cabecalho
    leCabecalhoIndice(f_ind, &c_ind);

    // se arquivo inconscistente, destroi e cria outro
    if (c_ind.status == '0')
    {
        destroiIndice(indice);
        func4(arqDados, indice);
        f_ind = fopen(indice, "rb");
        leCabecalhoIndice(f_ind, &c_ind);
    }

    // carrega indice para memoria primaria
    indice_dinamico = carregaIndice(f_ind, c_dados.nroRegArq);

    // status inconscistente
    c_ind.status = '0';

    // escreve inconscistente
    fwrite(&c_ind.status, sizeof(char), 1, f_ind);
    //fecha arquivo
    fclose(f_ind);

    // inicializa lista de removidos
    inicializar(&removidos);
    // carrega itens ja removidos, se houverem
    if (c_dados.nroRegRem > 0)
        carregaRemovidos(&removidos, f_dados);

    // percorrendo as n remocoes
    for (int i = 0; i < n; i++)
    {

        // le quantos campos serao utilizados na remocao
        scanf("%d", &qntd);

        // para cada busca, zera o eh_id
        eh_id = 0;

        // pega os campos
        for (int j = 0; j < qntd; j++)
        {
            // le o campo
            scanf("%s", campos[j]);
            //  verifica se é id
            if (strcmp(campos[j], "id") == 0)
            {
                scanf("%d", &intrs[j]);
                eh_id = 1;
            }

            // se nao for id, ve se eh idade
            else if (strcmp(campos[j], "idade") == 0)
                scanf("%d", &intrs[j]);
            // senao, é string
            else
                scan_quote_string(strs[j]);
        }

        // se algum campo é id - remove utilizando indice
        if (eh_id)
        {
            // remocao por id - utilizando indice
            remocaoID(indice_dinamico, f_dados, campos, strs, intrs, qntd, &c_dados, &removidos);
        }
        else
        {
            //  volta ao primeiro registro
            fseek(f_dados, 0, SEEK_SET);
            // pula o cabecalho
            pulaCabecalho(f_dados);
            // remocao sequencial
            remocaoSequencial(campos, strs, intrs, f_dados, indice_dinamico, qntd, &c_dados, &removidos);
        }
    }

    

    //abrimos um novo pq, como o novo indice vai ter menos entradas, no r+b ficaria com lixo no fim - modo wb destroi o que tinha antes
    abreArquivoBinario(&f_ind, indice, "wb");
    // reescrevendo -> indice agora esta ok
    c_ind.status = '1';
    // reescrevendo o cabecalho do indice
    escreveCabIndice(f_ind, &c_ind);
    // reescreve alteracoes no disco e ja da flcose -> fecha o arquivo
    escreveIndice(f_ind, &indice_dinamico, c_dados.nroRegArq);

    fclose(f_ind);

    // se possui arquivos removidos
    if (!vazia(&removidos))
    {
        c_dados.topo = removidos.primeiro->elemento.byteOffset;
        //  reescreve os removidos
        reescreveRemovidos(f_dados, &removidos);
    }
    else
    {
        c_dados.topo = -1;
    }
    // ja retorna o ponteiro ao inicio e escreve cabecalho
    escreveCabecalho(f_dados, &c_dados);

    // fecha dados
    fclose(f_dados);

    liberaLista(&removidos);

    binarioNaTela(arqDados);
    binarioNaTela(indice);
}

/// @brief Insere n registros no arquivo de dados e no de indice
/// @param arqDados nome do arquivo de dados
/// @param indice nome do arquivo de indice
/// @param n número de inserções a serem feitas
void func6(char *arqDados, char *indice, int n)
{
    FILE *f_dados, *f_ind;      // ponteiros de leitura e escrita dos arquivos de dados e de indice
    cabecalho c_dados;                // buffer para cabeçalho de arquivo de dados
    cabecalhoIndice c_indice;         // buffer para cabeçalho de arquivo de índice
    registro r_dados;                 // buffer para registro de arquivo de dados
    registroIndice r_indice;          // buffer para registro de arquivo de índice
    registroIndice *indice_dinamico = NULL; // vetor que armazena todos os índices do arquivo de índice
    t_lista removidos;          // lista de registros removidos do arquivo de dados
    t_lista removidos_ordenado; // lista de removidos ordenado

    // abre arquivo de dados para escrita
    abreArquivoBinario(&f_dados, arqDados, "r+b");

    // se tudo certinho le o cabecalho do arquivo de dados
    leCabecalho(f_dados, &c_dados);

    // verifica se esta conscistente
    if (c_dados.status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(f_dados);
        exit(0);
    }

    // verifica se o arquivo não está sem dados
    if (c_dados.nroRegArq == 0)
    {
        printf("Registro inesistente.\n");
        fclose(f_dados);
        exit(0);
    }

    // verifica se ja existe um arquivo de indice
    f_ind = fopen(indice, "r+b");
    // se nao tem, cria um
    if (f_ind == NULL)
    {
        func4(arqDados, indice);
        // como a funcionalidade 4 fecha o arquivo, abrimos novamente
        f_ind = fopen(indice, "r+b");
    }

    // le cabecalho
    leCabecalhoIndice(f_ind, &c_indice);

    // se arquivo inconscistente, destroi e cria outro
    if (c_indice.status == '0')
    {
        destroiIndice(indice);
        func4(arqDados, indice);
        f_ind = fopen(indice, "r+b");
        leCabecalhoIndice(f_ind, &c_indice);
    }

    // carrega indice para memoria primaria
    indice_dinamico = carregaIndice(f_ind, c_dados.nroRegArq);

    // status inconscistente
    c_indice.status = '0';

    // escreve inconscistente
    fwrite(&c_indice.status, sizeof(char), 1, f_ind);
    // salva a alteração
    fclose(f_ind);

    // inicializando as listas de registros removidos original e ordenada
    inicializar(&removidos);
    inicializar(&removidos_ordenado);

    // verifica se há registro no arquivo de dados
    if (c_dados.nroRegRem > 0)
    {
        // carrega lista de registros logicamente removidos do arquivo de dados
        carregaRemovidos(&removidos, f_dados);

        //volta ao inicio
        fseek(f_dados, 0, SEEK_SET);
        pulaCabecalho(f_dados);

        // carrega a lista de removidos ordenada inversamente por tamanho - logica best fit
        carregaRemOrd(&removidos_ordenado, f_dados);
    }

    // iitera nas n insercoes
    for (int i = 0; i < n; i++)
    {

        // recebe as entradas do novo registro, preenchendo o buffer para a inserção no arquivo e indice
        novoRegistro(&r_dados, &r_indice);

        // se o id ja estiver no arquivo, nao adiciona
        if (buscaBinaria(indice_dinamico, 0, c_dados.nroRegArq, r_dados.id) != -1)
        {
            break;
        }

        // se não há nenhum removido restante ou no arquivo, insere no final do arquivo de dados
        if (c_dados.topo == -1 || vazia(&removidos))
        {
            insereFinalArq(f_dados, &r_dados, &c_dados, &indice_dinamico, &r_indice);
        }
        else
        {
            // na lista ordenada de removidos, procura um novo espaço para inserir novo registro
            long bo_removido = achaTamanho(&removidos_ordenado, tamReal(r_dados));

            if (bo_removido == -1) // se a lista não tiver nenhum tamanho adequado
            {

                insereFinalArq(f_dados, &r_dados, &c_dados, &indice_dinamico, &r_indice);
            }
            else
            { // achou espaço compatível

                // byteoffset do novo registro a ser inserido, no registro de indice
                r_indice.byteoffset = bo_removido;

                // registro a ser sobrescrevido
                registro buffer_r;

                // posiciona no espaço selecionado para inserção
                fseek(f_dados, bo_removido, SEEK_SET);

                // recebe dados do registro logicamente removido que será sobrescrito
                leRegistroArquivo(f_dados, &buffer_r);

                // volta ponteiro para onde novo registro será escrito
                fseek(f_dados, bo_removido, SEEK_SET);

                // insere sequencialmente
                // tamanho do registro, é o tamanho do registro a ser substituído
                r_dados.tamanhoRegistro = buffer_r.tamanhoRegistro;
                // escreve no arquivo
                escreveRegistroArquivo(f_dados, &r_dados);

                // ao escrever o registro no arquivo, o ponteiro está no final do registro novo - pode ser que nao no fim do registro em si
                if (ftell(f_dados) < (bo_removido + r_dados.tamanhoRegistro))
                {
                    // caso necessário, preenche com $ os espaços faltantes
                    reutilizaEspaco(f_dados, bo_removido + r_dados.tamanhoRegistro);
                }

                // insere novo registro no indice
                insereIndice(&indice_dinamico, r_indice, c_dados.nroRegArq);

                // remove o registro removido das listas de removidos
                remover(bo_removido, &removidos);
                remover(bo_removido, &removidos_ordenado);

                // decrementa o numero de arquivos removidos
                c_dados.nroRegRem--;

                // libera strings buffer
                liberaRegistro(&buffer_r);
            }
        }
        // incrementa numero de arquivos nao removidos
        c_dados.nroRegArq++;
    }

    // atualiza cabeçalho de ambos arquivos binários
    c_dados.status = '1';
    c_indice.status = '1';

    

    // reescreve a lista de registros removidos no arquivo de dados
    if (!vazia(&removidos))
    {
        c_dados.topo = removidos.primeiro->elemento.byteOffset;
        // para reescrita, utilizamos a lista que mantem a logica da pilha de removidos
        reescreveRemovidos(f_dados, &removidos);
    }
    else
    {
        c_dados.topo = -1;
    }

    // reescreve arquivo de dados
    escreveCabecalho(f_dados, &c_dados);
    

    // reescreve índice - reabre para evitar lixo
    abreArquivoBinario(&f_ind, indice, "wb");
    escreveCabIndice(f_ind, &c_indice);
    escreveIndice(f_ind, &indice_dinamico, c_dados.nroRegArq);

    // libera espaço alocado
    liberaLista(&removidos);
    liberaLista(&removidos_ordenado);

    // fecha arquivos
    fclose(f_dados);
    fclose(f_ind);

    // funcionalidades fornecidas
    binarioNaTela(arqDados);
    binarioNaTela(indice);
}
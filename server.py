import socket
import os
from programa import *
import re

# Define o host e a porta
HOST = 'localhost'
PORT = 12345

# Cria um objeto de socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Vincula o socket ao host e à porta
server_socket.bind((HOST, PORT))

# Coloca o socket em modo de escuta para aceitar conexões
server_socket.listen(1)
print(f'Server listening on {HOST}:{PORT}...')

# Dicionário para armazenar arquivos abertos
arquivos_abertos = {}

# Função para abrir um arquivo binário
def abrir_arquivo(nome_arquivo):
    if nome_arquivo in arquivos_abertos:
        return "ERRO: Arquivo já está aberto."
    try:
        arquivo = open(nome_arquivo, 'rb')
        arquivos_abertos[nome_arquivo] = arquivo
        return "OK"
    except Exception as e:
        return f"ERRO: {str(e)}"

# Função para fechar um arquivo binário
def fechar_arquivo(nome_arquivo):
    if nome_arquivo not in arquivos_abertos:
        return "ERRO: Arquivo não está aberto."
    try:
        arquivos_abertos[nome_arquivo].close()
        del arquivos_abertos[nome_arquivo]
        return "OK"
    except Exception as e:
        return f"ERRO: {str(e)}"

# Aceita uma conexão
client_socket, client_address = server_socket.accept()
print(f'Connection from {client_address} established.')

try:
    while True:
        # Recebe dados do cliente
        data = client_socket.recv(1024).decode('ascii')
        if not data:
            break
        print(f'Received from client: {data}')
        
        lines = data.split("\n")
        # for line in lines:
        #     print(line)

        cmd = lines[0].split(" ")[0]
        nome_arquivo= lines[0].split(" ")[1]
        #print(cmd)
        #print(nome_arquivo)

        if (cmd == "2"): # listar
            print("Listagem de registros: ")
            response = listagemRegistros(nome_arquivo)

            listFileName = "listagem.txt"
            f = open(listFileName, "w")
            f.write(response)
            f.close()
            
            print("Abra " + listFileName + " para visualizar a lista de registros")

        elif (cmd == "3"): # buscar
            #print("Fazendo a busca...")
            response = buscaPelaFunc3(nome_arquivo, lines[1])
            print(response)

        elif(cmd == "5"): # remover

            # TODO: testar! ele roda de boa sem dar erro, mas depois pra abrir
            # o arquivo pela listagem dá segfault :(
            print("Removendo o registro...")

            nome_indice = lines[0].split(" ")[2]
            e = removerRegistro(nome_arquivo, "indice.bin", lines[1])

            print(e)
            if (e < 0):
                print("Falha" + str(e) + " ao remover o registro")
            else:
                print("Registro removido!")

        elif (cmd == "7"): # alterar
            print("Alterando o registro...")
            nome_indice = lines[0].split(" ")[2]
            target_id = lines[1].split(" ")[2]

            target = lines[2].split(" ")
            idade = target[4]

            pattern = r'"(.*?)"'
            strings = re.findall(pattern, lines[2])

            nomeJogador = strings[0]
            nacionalidade = strings[1]
            clube = strings[2]

            # print(nome_indice, target_id, idade, nomeJogador, nacionalidade, clube)
            

        #cmd = data.split("\n")[0]
        
        # func = cmd.split(" ")[0]
        # nome_arquivo = cmd.split(" ")[1]
        # n_exec = cmd.split(" ")[2]

        # if (func == "3"):
            
        
        # Processa o comando recebido
        if data.startswith("open "):
            nome_arquivo = data.split(" ", 1)[1]
            response = abrir_arquivo(nome_arquivo)
        elif data.startswith("close "):
            nome_arquivo = data.split(" ", 1)[1]
            response = fechar_arquivo(nome_arquivo)
        else:
            response = "ERRO: Comando desconhecido."

        # Envia uma resposta de volta para o cliente
        client_socket.sendall(response.encode('ascii'))

finally:
    # Fecha a conexão
    client_socket.close()
    server_socket.close()
    print('Server closed.')

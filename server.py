import socket
import os
from programa import buscaPelaFunc3

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

        # Processa o comando recebido
        if data.startswith("open "):
            nome_arquivo = data.split(" ", 1)[1]
            response = abrir_arquivo(nome_arquivo)
        elif data.startswith("close "):
            nome_arquivo = data.split(" ", 1)[1]
            response = fechar_arquivo(nome_arquivo)
        elif data.startswith("search"):
            # return 
            response = buscaPelaFunc3()
        else:
            response = "ERRO: Comando desconhecido."

        # Envia uma resposta de volta para o cliente
        client_socket.sendall(response.encode('ascii'))

finally:
    # Fecha a conexão
    client_socket.close()
    server_socket.close()
    print('Server closed.')

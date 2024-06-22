import socket  # Importa o módulo de socket

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

# Aceita uma conexão
client_socket, client_address = server_socket.accept()
print(f'Connection from {client_address} established.')

try:
    while True:  # Loop para continuar recebendo dados do cliente
        # Recebe dados do cliente
        data = client_socket.recv(1024).decode('utf-8')
        if not data:  # Se não receber dados, sai do loop
            break
        print(f'Received from client: {data}')

        # Envia uma resposta de volta para o cliente
        response = f'Server received: {data}'
        client_socket.sendall(response.encode('utf-8'))

finally:
    # Fecha a conexão
    client_socket.close()
    server_socket.close()
    print('Server closed.')

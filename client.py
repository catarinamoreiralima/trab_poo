import socket  # Importa o módulo de socket para comunicação de rede
import threading  # Importa o módulo de threading para executar threads

def receive_messages(client_socket):
    while True:
        try:
            message = client_socket.recv(1024).decode('ascii')
            if message:
                print(message)# Imprime a mensagem recebida do servidor
        except:
            print("An error occurred!")  # Imprime uma mensagem de erro se ocorrer um problema
            client_socket.close()  # Fecha o socket do cliente
            break

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Cria um socket TCP
    client_socket.connect(('127.0.0.1', 5556))  # Conecta ao servidor na porta 5555

    threading.Thread(target=receive_messages, args=(client_socket,)).start()  # Inicia uma thread para receber mensagens

    while True:
        message = input("")  # Lê a mensagem do usuário
        client_socket.send(message.encode('ascii'))  # Envia a mensagem ao servidor

if __name__ == "__main__":
    main()  # Executa a função principal do cliente

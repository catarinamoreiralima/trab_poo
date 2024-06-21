import socket
import threading

def receive_messages(client_socket):
    while True:
        try:
            message = client_socket.recv(1024).decode('utf-8')
            if message:
                print(message)
        except:
            print("An error occurred!")
            client_socket.close()
            break

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 5556))

    threading.Thread(target=receive_messages, args=(client_socket,)).start()

    while True:
        message = input("")
        client_socket.send(message.encode('utf-8'))

if __name__ == "__main__":
    main()

import java.io.*;  // Importa classes para entrada e saída
import java.net.*;  // Importa classes para trabalhar com rede

public class JavaSocketClient {
    public static void main(String[] args) {
        String host = "localhost";  // Define o host (servidor)
        int port = 12345;  // Define a porta
        try (Socket socket = new Socket(host, port)) {  // Tenta conectar ao servidor
            // Cria streams de entrada e saída
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));

            String userInput;
            System.out.println("Enter a message to send to the server or 'exit' to quit:");
            while ((userInput = stdIn.readLine()) != null) {  // Lê entrada do usuário
                if ("exit".equalsIgnoreCase(userInput)) {  // Se o usuário digitar 'exit', sai do loop
                    break;
                }
                // Envia a entrada do usuário para o servidor
                out.println(userInput);

                // Lê a resposta do servidor
                String response = in.readLine();
                System.out.println("Server response: " + response);
            }
        } catch (UnknownHostException e) {
            System.err.println("Don't know about host " + host);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for the connection to " + host);
            System.exit(1);
        }
    }
}

import java.io.*;
import java.net.*;

public class ChatClient {
    private Socket socket;
    private BufferedReader reader;
    private PrintWriter writer;

    public ChatClient(String address, int port) {
        try {
            socket = new Socket(address, port);
            reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            writer = new PrintWriter(socket.getOutputStream(), true);

            new Thread(new ReceiveMessages()).start();

            BufferedReader consoleReader = new BufferedReader(new InputStreamReader(System.in));
            String message;
            while ((message = consoleReader.readLine()) != null) {
                writer.println(message);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private class ReceiveMessages implements Runnable {
        public void run() {
            String message;
            try {
                while ((message = reader.readLine()) != null) {
                    System.out.println(message);
                }
            } catch (IOException e) {
                System.err.println("Connection lost or an error occurred.");
                e.printStackTrace();
            } finally {
                try {
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }




    public static void main(String[] args) {
        new ChatClient("127.0.0.1", 5556);
    }
}

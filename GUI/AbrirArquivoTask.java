import javax.swing.*;
import java.io.*;
//import java.net.Socket;

public class AbrirArquivoTask extends SwingWorker<String, Void> {
    private PrintWriter out;
    private BufferedReader in;
    private String nomeArqBin;

    public AbrirArquivoTask(PrintWriter out, BufferedReader in, String nomeArqBin) {
        this.out = out;
        this.in = in;
        this.nomeArqBin = nomeArqBin;
    }

    @Override
    protected String doInBackground() throws Exception {
        out.println("open " + nomeArqBin);
        return in.readLine();
    }

    @Override
    protected void done() {
        try {
            String response = get();
            if (response.equals("OK")) {
                JOptionPane.showMessageDialog(null, "Arquivo aberto com sucesso!");
            } else {
                JOptionPane.showMessageDialog(null, "Erro ao abrir o arquivo.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

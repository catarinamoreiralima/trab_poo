import javax.swing.*;
import java.io.*;

public class FecharArquivoTask extends SwingWorker<String, Void> {
    private PrintWriter out;
    private BufferedReader in;
    private String nomeArqBin;

    public FecharArquivoTask(PrintWriter out, BufferedReader in, String nomeArqBin) {
        this.out = out;
        this.in = in;
        this.nomeArqBin = nomeArqBin;
    }

    @Override
    protected String doInBackground() throws Exception {
        out.println("close " + nomeArqBin);
        return in.readLine();
    }

    @Override
    protected void done() {
        try {
            String response = get();
            if (response.equals("OK")) {
                JOptionPane.showMessageDialog(null, "Arquivo fechado com sucesso!");
            } else {
                JOptionPane.showMessageDialog(null, "Erro ao fechar o arquivo.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

import javax.swing.*;
import java.awt.event.*;
import java.io.*;
import java.net.Socket;

public class FifaGUI extends JFrame implements ActionListener {

    private JLabel label_id;
    private JLabel label_idade;
    private JLabel label_nomeJogador;
    private JLabel label_nacionalidade;
    private JLabel label_nomeClube;
    private JTextField id;
    private JTextField idade;
    private JTextField nomeJogador;
    private JTextField nacionalidade;
    private JTextField nomeClube;
    private JButton buttonOK;

    private Socket socket;
    private PrintWriter out;

    public FifaGUI() {
        try {
            socket = new Socket("localhost", 12345);  // conecta ao servidor
            out = new PrintWriter(socket.getOutputStream(), true);
        } catch (IOException e) {
            e.printStackTrace();
        }

        JPanel jp = (JPanel) this.getContentPane();
        jp.setLayout(new BoxLayout(jp, BoxLayout.Y_AXIS));

        // cria menu
        JMenuBar menuBar = new JMenuBar();
        setJMenuBar(menuBar);

        JMenu menuArquivos = new JMenu("Arquivos");
        menuBar.add(menuArquivos);

        JMenuItem itemAbrir = new JMenuItem("Abrir");
        itemAbrir.setActionCommand("abrir_arquivo");
        itemAbrir.addActionListener(this);
        menuArquivos.add(itemAbrir);

        JMenuItem itemFechar = new JMenuItem("Fechar");
        itemFechar.setActionCommand("fechar");
        itemFechar.addActionListener(this);
        menuArquivos.add(itemFechar);

        JMenu menuCriar = new JMenu("Criar");

        JMenuItem subMenuTexto = new JMenuItem("Texto");
        subMenuTexto.setActionCommand("criar_texto");
        subMenuTexto.addActionListener(this);
        menuCriar.add(subMenuTexto);

        JMenuItem subMenuBinario = new JMenuItem("Binário");
        subMenuBinario.setActionCommand("criar_binario");
        subMenuBinario.addActionListener(this);
        menuCriar.add(subMenuBinario);

        menuArquivos.add(menuCriar);

        JMenuItem itemSair = new JMenuItem("Sair");
        itemSair.setActionCommand("sair");
        itemSair.addActionListener(this);
        menuArquivos.add(itemSair);

        // Layout para busca inicial dos registros
        label_id = new JLabel("ID:");
        id = new JTextField(50);

        label_idade = new JLabel("Idade:");
        idade = new JTextField(50);

        label_nomeJogador = new JLabel("Nome do Jogador:");
        nomeJogador = new JTextField(50);

        label_nacionalidade = new JLabel("Nacionalidade:");
        nacionalidade = new JTextField(50);

        label_nomeClube = new JLabel("Nome do Clube:");
        nomeClube = new JTextField(50);

        buttonOK = new JButton("Procurar");
        buttonOK.addActionListener(this);

        jp.add(label_id);
        jp.add(id);
        jp.add(label_idade);
        jp.add(idade);
        jp.add(label_nomeJogador);
        jp.add(nomeJogador);
        jp.add(label_nacionalidade);
        jp.add(nacionalidade);
        jp.add(label_nomeClube);
        jp.add(nomeClube);
        jp.add(buttonOK);

        setTitle("FIFINHA");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setSize(400, 300);
        setLocationRelativeTo(null);
    }

    @Override
    public void actionPerformed(ActionEvent e) {

        String comando = e.getActionCommand();

        switch (comando) {
            case "abrir_arquivo":
                JOptionPane.showMessageDialog(this, "Abrir selecionado!");
                break;
            case "fechar":
                JOptionPane.showMessageDialog(this, "Fechar selecionado!");
                break;
            case "criar_texto":
                JOptionPane.showMessageDialog(this, "Texto selecionado!");
                break;
            case "criar_binario":
                JOptionPane.showMessageDialog(this, "Binário selecionado!");
                break;
            case "sair":
                int option = JOptionPane.showConfirmDialog(this, "Deseja realmente sair?", "Confirmação", JOptionPane.YES_NO_OPTION);
                if (option == JOptionPane.YES_OPTION) {
                    try {
                        socket.close();
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                    System.exit(0);
                }
                break;
            case "Procurar":
            StringBuilder searchQueryBuilder = new StringBuilder();
            StringBuilder campos = new StringBuilder(); // buffer que guardará os campos digitados
            int cont = 0; // contará quantos campos foram escritos na gui
            
            searchQueryBuilder.append("3 binario.bin 1\n");
            if (!id.getText().trim().isEmpty()) {
                campos.append("id ").append(id.getText().trim()).append(" ");
                cont++;
            }
            if (!idade.getText().trim().isEmpty()) {
                campos.append("idade ").append(idade.getText().trim()).append(" ");
                cont++;
            }
            if (!nomeJogador.getText().trim().isEmpty()) {
                campos.append("nome ").append("\"").append(nomeJogador.getText().trim()).append("\"").append(" ");
                cont++;
            }
            if (!nacionalidade.getText().trim().isEmpty()) {
                campos.append("nacionalidade ").append("\"").append(nacionalidade.getText().trim()).append("\"").append(" ");
                cont++;
            }
            if (!nomeClube.getText().trim().isEmpty()) {
                campos.append("clube ").append("\"").append(nomeClube.getText().trim()).append("\"").append(" ");
                cont++;
            }

            searchQueryBuilder.append(cont).append(" ").append(campos);

            // remove o último " " se tiver
            String searchQuery = searchQueryBuilder.toString();
            if (searchQuery.endsWith(" ")) {
                searchQuery = searchQuery.substring(0, searchQuery.length() - 1);
            }

            out.println(searchQuery);

            break;
        default:
            break;
        }
    }
}

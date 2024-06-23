import javax.swing.*;
import java.awt.*;
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
    private JButton remover;
    private JButton alterar;

    private JTextArea instrucoes;

    private Socket socket;
    private PrintWriter out;
    private BufferedReader in;
    private String nomeArqBin;

    public FifaGUI() {
        try {
            socket = new Socket("localhost", 12345); // conecta ao servidor
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        } catch (IOException e) {
            e.printStackTrace();
        }

        JPanel jp = (JPanel) this.getContentPane();
        jp.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5); // Espaçamento entre componentes

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

        JMenuItem itemListagem = new JMenuItem("Listagem");
        itemListagem.setActionCommand("listagem");
        itemListagem.addActionListener(this);
        menuArquivos.add(itemListagem);

        JMenuItem itemSair = new JMenuItem("Sair");
        itemSair.setActionCommand("sair");
        itemSair.addActionListener(this);
        menuArquivos.add(itemSair);

        // Layout para busca inicial dos registros
        instrucoes = new JTextArea(
                "Para realizar a PESQUISA, preencha ao menos um dos campos e clique em \"Pesquisar\"\n"
                        + "Para realizar a REMOÇÃO, preencha o ID do jogador que deseja remover e clique em \"Remover\"\n"
                        + "Para realizar a ALTERAÇÃO do dados de algum jogador, preencha todos os campos e pressione \"Alterar\"");
        instrucoes.setEditable(false);
        instrucoes.setLineWrap(true);
        instrucoes.setWrapStyleWord(true);
        instrucoes.setOpaque(false);

        label_id = new JLabel("ID:");
        id = new JTextField(20);

        label_idade = new JLabel("Idade:");
        idade = new JTextField(20);

        label_nomeJogador = new JLabel("Nome do Jogador:");
        nomeJogador = new JTextField(20);

        label_nacionalidade = new JLabel("Nacionalidade:");
        nacionalidade = new JTextField(20);

        label_nomeClube = new JLabel("Nome do Clube:");
        nomeClube = new JTextField(20);

        buttonOK = new JButton("Procurar");
        buttonOK.setActionCommand("Procurar");
        buttonOK.addActionListener(this);

        remover = new JButton("Remover");
        remover.setActionCommand("Remover");
        remover.addActionListener(this);

        alterar = new JButton("Alterar");
        alterar.setActionCommand("Alterar");
        alterar.addActionListener(this);

        // Adiciona componentes ao painel principal com GridBagLayout
        gbc.anchor = GridBagConstraints.WEST;
        gbc.fill = GridBagConstraints.HORIZONTAL;

        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 2;
        jp.add(instrucoes, gbc);

        gbc.gridwidth = 1;
        gbc.gridy++;
        jp.add(label_id, gbc);

        gbc.gridx = 1;
        jp.add(id, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        jp.add(label_idade, gbc);

        gbc.gridx = 1;
        jp.add(idade, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        jp.add(label_nomeJogador, gbc);

        gbc.gridx = 1;
        jp.add(nomeJogador, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        jp.add(label_nacionalidade, gbc);

        gbc.gridx = 1;
        jp.add(nacionalidade, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        jp.add(label_nomeClube, gbc);

        gbc.gridx = 1;
        jp.add(nomeClube, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        gbc.gridwidth = 2;
        gbc.fill = GridBagConstraints.NONE;
        gbc.anchor = GridBagConstraints.CENTER;
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(buttonOK);
        buttonPanel.add(remover);
        buttonPanel.add(alterar);
        jp.add(buttonPanel, gbc);

        setTitle("FIFINHA");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setSize(400, 360);
        setLocationRelativeTo(null);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String comando = e.getActionCommand();

        switch (comando) {
            case "abrir_arquivo":
                abrirArquivoBinario();
                break;
            case "fechar":
                fecharArquivoBinario();
                break;
            case "listagem":
                if (nomeArqBin == null) {
                    JOptionPane.showMessageDialog(this, "Por favor, carregue um arquivo primeiro!", "Erro",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }

                StringBuilder chamaFunc2 = new StringBuilder();
                chamaFunc2.append("2 ").append(nomeArqBin);
                out.println(chamaFunc2);

                JOptionPane.showMessageDialog(this, "Verifique que o resultado da listagem está no terminal!");

                break;
            case "sair":
                int option = JOptionPane.showConfirmDialog(this, "Deseja realmente sair?", "Confirmação",
                        JOptionPane.YES_NO_OPTION);
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
                verificaSeTemArquivo();

                boolean algumCampoPreenchido = !id.getText().trim().isEmpty() ||
                        !idade.getText().trim().isEmpty() ||
                        !nomeJogador.getText().trim().isEmpty() ||
                        !nacionalidade.getText().trim().isEmpty() ||
                        !nomeClube.getText().trim().isEmpty();

                if (!algumCampoPreenchido) {
                    JOptionPane.showMessageDialog(this,
                            "Por favor, preencha ao menos um campo para realizar a pesquisa.", "Erro",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }

                chamaFunc3();

                JOptionPane.showMessageDialog(this, "Verifique que o resultado da pesquisa está no terminal!");

                break;
            case "Remover":
                verificaSeTemArquivo();

                boolean idPreenchido = !id.getText().trim().isEmpty();

                if (!idPreenchido) {
                    JOptionPane.showMessageDialog(this,
                            "Por favor, preencha o campo ID para realizar a remoção.", "Erro",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }

                StringBuilder retornoRemover = new StringBuilder();
                retornoRemover.append("5 ").append(nomeArqBin).append(" ").append("indice.bin").append(" 1\n").append("1 ")
                        .append(id.getText().trim());
                out.println(retornoRemover);
                break;
            case "Alterar":
                verificaSeTemArquivo();

                boolean todosCamposPreenchidos = !id.getText().trim().isEmpty() &&
                        !idade.getText().trim().isEmpty() &&
                        !nomeJogador.getText().trim().isEmpty() &&
                        !nacionalidade.getText().trim().isEmpty() &&
                        !nomeClube.getText().trim().isEmpty();

                if (!todosCamposPreenchidos) {
                    JOptionPane.showMessageDialog(this,
                            "Por favor, preencha todos os campos para realizar a alteração.", "Erro",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }

                StringBuilder retornoAlterar = new StringBuilder();
                retornoAlterar.append("7 ").append(nomeArqBin).append(" ").append("indice.bin 1\n").append("1 id ")
                        .append(id.getText().trim()).append('\n').append("1 id ")
                        .append(id.getText().trim()).append(" idade ").append(idade.getText().trim())
                        .append(" nomeJogador ").append("\"").append(nomeJogador.getText().trim()).append("\"")
                        .append(" nacionalidade ").append("\"").append(nacionalidade.getText().trim()).append("\"")
                        .append(" clube ").append("\"").append(nomeClube.getText().trim()).append("\"");
                out.println(retornoAlterar);

                break;
            default:
                break;
        }
    }

    private void verificaSeTemArquivo() {
        if (nomeArqBin == null) {
            JOptionPane.showMessageDialog(this, "Por favor, carregue um arquivo primeiro!", "Erro",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
    }

    private void abrirArquivoBinario() {
        JFileChooser ecolheArq = new JFileChooser();
        int returnValue = ecolheArq.showOpenDialog(this);

        if (returnValue == JFileChooser.APPROVE_OPTION) {
            File arquivoSelecionado = ecolheArq.getSelectedFile();
            nomeArqBin = arquivoSelecionado.getName(); // Obter apenas o nome do arquivo

            // cria e executa a tarefa de abrir o arquivo
            AbrirArquivoTask task = new AbrirArquivoTask(out, in, arquivoSelecionado.getAbsolutePath());
            task.execute();
        }
    }

    private void fecharArquivoBinario() {
        if (nomeArqBin != null) {
            // cria e executa a tarefa de fechar o arquivo
            FecharArquivoTask task = new FecharArquivoTask(out, in, nomeArqBin);
            task.execute();

            // Definir nomeArqBin como null para indicar que nenhum arquivo está aberto
            nomeArqBin = null;
        } else {
            JOptionPane.showMessageDialog(this, "Nenhum arquivo aberto para fechar.");
        }
    }

    private void chamaFunc3() {
        StringBuilder searchQueryBuilder = new StringBuilder();
        StringBuilder campos = new StringBuilder(); // buffer que guardará os campos digitados
        int cont = 0; // contará quantos campos foram escritos na gui

        searchQueryBuilder.append("3 ").append(nomeArqBin).append(" 1\n");
        if (!id.getText().trim().isEmpty()) {
            campos.append("id ").append(id.getText().trim()).append(" ");
            cont++;
        } else {
            if (!idade.getText().trim().isEmpty()) {
                campos.append("idade ").append(idade.getText().trim()).append(" ");
                cont++;
            }
            if (!nomeJogador.getText().trim().isEmpty()) {
                campos.append("nomeJogador ").append("\"").append(nomeJogador.getText().trim()).append("\"")
                        .append(" ");
                cont++;
            }
            if (!nacionalidade.getText().trim().isEmpty()) {
                campos.append("nacionalidade ").append("\"").append(nacionalidade.getText().trim()).append("\"")
                        .append(" ");
                cont++;
            }
            if (!nomeClube.getText().trim().isEmpty()) {
                campos.append("clube ").append("\"").append(nomeClube.getText().trim()).append("\"").append(" ");
                cont++;
            }
        }

        searchQueryBuilder.append(cont).append(" ").append(campos);

        // remove o último " " se tiver
        String searchQuery = searchQueryBuilder.toString();
        if (searchQuery.endsWith(" ")) {
            searchQuery = searchQuery.substring(0, searchQuery.length() - 1);
        }

        out.println(searchQuery);
    }
}

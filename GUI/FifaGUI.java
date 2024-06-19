import javax.swing.*;
import java.awt.event.*;

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

    public FifaGUI() {

        JPanel jp = (JPanel) this.getContentPane();
        jp.setLayout(new BoxLayout(jp, BoxLayout.Y_AXIS)); // layout vertical

        // Criação do menu
        JMenuBar menuBar = new JMenuBar();
        setJMenuBar(menuBar);

        // Menu "Arquivos"
        JMenu menuArquivos = new JMenu("Arquivos");
        menuBar.add(menuArquivos);

        // Item "Abrir"
        JMenuItem itemAbrir = new JMenuItem("Abrir");
        itemAbrir.setActionCommand("abrir_arquivo");
        itemAbrir.addActionListener(this);
        menuArquivos.add(itemAbrir);

        // Item "Fechar"
        JMenuItem itemFechar = new JMenuItem("Fechar");
        itemFechar.setActionCommand("fechar");
        itemFechar.addActionListener(this);
        menuArquivos.add(itemFechar);

        // Menu "Criar"
        JMenu menuCriar = new JMenu("Criar");

        // Submenu "Texto"
        JMenuItem subMenuTexto = new JMenuItem("Texto");
        subMenuTexto.setActionCommand("criar_texto");
        subMenuTexto.addActionListener(this);
        menuCriar.add(subMenuTexto);

        // Submenu "Binário"
        JMenuItem subMenuBinario = new JMenuItem("Binário");
        subMenuBinario.setActionCommand("criar_binario");
        subMenuBinario.addActionListener(this);
        menuCriar.add(subMenuBinario);

        menuArquivos.add(menuCriar);

        // Item "Sair"
        JMenuItem itemSair = new JMenuItem("Sair");
        itemSair.setActionCommand("sair");
        itemSair.addActionListener(this);
        menuArquivos.add(itemSair);

        // Layout para busca inicial dos registros
        // campo ID
        label_id = new JLabel("ID:");
        id = new JTextField(20); // Define um tamanho preferencial para o campo

        // campo IDADE
        label_idade = new JLabel("Idade:");
        idade = new JTextField(20);

        // campo NOME JOGADOR
        label_nomeJogador = new JLabel("Nome do Jogador:");
        nomeJogador = new JTextField(20);

        // campo NACIONALIDADE
        label_nacionalidade = new JLabel("Nacionalidade:");
        nacionalidade = new JTextField(20);

        // campo NOME DO CLUBE
        label_nomeClube = new JLabel("Nome do Clube:");
        nomeClube = new JTextField(20);

        buttonOK = new JButton("Procurar");
        buttonOK.addActionListener(this); // Adiciona o ActionListener ao botão

        // Adiciona os componentes na ordem desejada
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

        // Configurações do JFrame
        setTitle("FIFINHA");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Sai no "x"
        setResizable(false);
        setSize(400, 300); // Tamanho da GUI
        setLocationRelativeTo(null); // Centraliza a janela na tela
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String comando = e.getActionCommand();

        switch (comando) {
            case "abrir_arquivo": // selecionou "abrir" menu
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
                    System.exit(0);
                }
                break;
            case "Procurar":
                JOptionPane.showMessageDialog(this, "Botão Procurar foi clicado!");
                break;
            default:
                break;
        }
    }
}
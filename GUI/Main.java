
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) throws Exception {

        FifaGUI frame = new FifaGUI();
        frame.setVisible(true);

        String registrosString = obterRegistrosDoServidor();

        // separa os registros em uma lista de RegistroFIFA
        List<RegistroFIFA> registros = separarRegistros(registrosString);

    }

    // método para separar os registros em uma lista de RegistroFIFA
    private static List<RegistroFIFA> separarRegistros(String registrosString) {
        List<RegistroFIFA> listaRegistros = new ArrayList<>();

        // divide a string por linhas (registros)
        String[] linhas = registrosString.split("\n");

        // processa cada linha para criar objetos RegistroFIFA
        for (String linha : linhas) {

            // divide a linha em campos
            String[] campos = linha.split(";");

            // extrai informações dos campos
            int id = Integer.parseInt(campos[0].trim());
            int idade = Integer.parseInt(campos[1].trim());
            String nomeJogador = campos[2].trim();
            String nacionalidade = campos[3].trim();
            String nomeClube = campos[4].trim();

            // cria objeto RegistroFIFA e adicionar à lista
            RegistroFIFA registro = new RegistroFIFA(id, idade, nomeJogador, nacionalidade, nomeClube);
            listaRegistros.add(registro);
        }

        return listaRegistros;
       
    };
}

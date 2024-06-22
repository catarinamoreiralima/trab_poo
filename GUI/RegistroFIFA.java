public class RegistroFIFA {
    private String id;
    private String nomeJogador;
    private String idade;
    private String nacionalidade;
    private String nomeClube;

    public RegistroFIFA(String id, String nomeJogador, String idade, String nacionalidade, String nomeClube) {
        this.id = id;
        this.nomeJogador = nomeJogador;
        this.idade = idade;
        this.nacionalidade = nacionalidade;
        this.nomeClube = nomeClube;
    }

    public String getId() {
        return id;
    }

    public String getNomeJogador() {
        return nomeJogador;
    }

    public String getIdade() {
        return idade;
    }

    public String getNacionalidade() {
        return nacionalidade;
    }

    public String getNomeClube() {
        return nomeClube;
    }

    @Override
    public String toString() {
        return id + " - " + nomeJogador;
    }
}

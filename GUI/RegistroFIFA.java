

public class RegistroFIFA {
    private int id;
    private int idade;
    private String nomeJogador;
    private String nacionalidade;
    private String nomeClube;

    public RegistroFIFA(int id, int idade, String nomeJogador, String nacionalidade, String nomeClube) {
        this.id = id;
        this.idade = idade;
        this.nomeJogador = nomeJogador;
        this.nacionalidade = nacionalidade;
        this.nomeClube = nomeClube;
    }


    public int getId() {
        return id;
    }

    public int getIdade() {
        return idade;
    }

    public String getNomeJogador() {
        return nomeJogador;
    }

    public String getNacionalidade() {
        return nacionalidade;
    }

    public String getNomeClube() {
        return nomeClube;
    }

}


import ctypes

# load c lib
lib = ctypes.CDLL('./lib.so')


def arquivosTest():

    b1 = "@|12|marcos|@|palmeiras$asd"
    b_b1 = b1.encode("ascii")
    lib.buscaHandler.argtypes = [ctypes.c_char_p]
    lib.buscaHandler(b_b1)

def func4Test():
    nomeInd = "indice1.bin"
    nomeArqDados = "binario1.bin"

    b_nomeInd = nomeInd.encode("ascii")
    b_nomeArqDados = nomeArqDados.encode("ascii")

    lib.func4.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
    lib.func4(b_nomeArqDados, b_nomeInd)


def initArquivo(nomeArqDados):
    nomeInd = "indiceMain.bin"

    b_nomeArqDados = nomeArqDados.encode("ascii")
    b_nomeInd = nomeInd.encode("ascii")

    lib.func4.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
    lib.func4(b_nomeArqDados, b_nomeInd)

#todo: testar 
def buscaPelaFunc3():
    nomeArqDados = input("Insira o nome do arquivo de dados: ")
    buscainput = "add aq"

    b_nomeArqDados = nomeArqDados.encode("ascii")
    b_buscainput = buscainput.encode("ascii")

    lib.func3POO.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
    lib.func3POO(b_nomeArqDados, 1, b_buscainput)

def main():
    # Code to be executed when the script is run directly
    # basicTest()
    # buscaTest()
    # arquivosTest()
    # func4Test()

    #nomeArqDados = input("Insira o nome do arquivo de dados: ")
    #initArquivo(nomeArqDados)


if __name__ == "__main__":
    main()
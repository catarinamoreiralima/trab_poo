import ctypes

lib = ctypes.CDLL('./lib.so')


def buscaPelaFunc3():
    nomeArqDados = input("Insira o nome do arquivo de dados: ")
    buscainput = '1 id 225193'

    b_nomeArqDados = nomeArqDados.encode("ascii")
    b_buscainput = buscainput.encode("ascii")

    lib.func3POO.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p]
    str = lib.func3POO(b_nomeArqDados, 1, b_buscainput)
    print(str)

if __name__ == "__main__":
    buscaPelaFunc3()
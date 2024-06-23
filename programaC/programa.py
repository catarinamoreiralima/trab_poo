import ctypes

lib = ctypes.CDLL('./lib.so')


def buscaPelaFunc3():
    nomeArqDados = input("Insira o nome do arquivo de dados: ")
    buscainput = input("Insira a busca: ")

    # encode strings de input
    b_nomeArqDados = nomeArqDados.encode("ascii")
    b_buscainput = buscainput.encode("ascii")

    # sets function types for input and output
    lib.func3POO.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p]
    lib.func3POO.restype = ctypes.c_char_p

    str = lib.func3POO(b_nomeArqDados, 1, b_buscainput)
    str = str.decode("ascii")
    print(str)


if __name__ == "__main__":
    buscaPelaFunc3()
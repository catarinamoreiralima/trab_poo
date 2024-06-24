import ctypes

lib = ctypes.CDLL('./lib.so')



def buscaPelaFunc3(nomeArqDados, buscainput):
    #nomeArqDados = "binario6.bin"
    #buscainput = '1 id 225193'

    # encode strings de input
    b_nomeArqDados = nomeArqDados.encode("ascii")
    b_buscainput = buscainput.encode("ascii")


    # sets function types for input and output
    lib.func3POO.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p]
    lib.func3POO.restype = ctypes.c_char_p

    #print("a")
    str = lib.func3POO(b_nomeArqDados, 1, b_buscainput)
    str = str.decode("ascii") + "\n"
    #print(str)
    return str

def listagemRegistros(nomeArqDados):
    b_nomeArqDados = nomeArqDados.encode("ascii")

    lib.func2POO.argtypes = [ctypes.c_char_p]
    lib.func2POO.restype = ctypes.c_char_p

    str = lib.func2POO(b_nomeArqDados)
    str = str.decode("ascii")
    # print(str)
    return str

def removerRegistro(nomeArqDados, nomeIndice, user_input):
    b_nomeArqDados = nomeArqDados.encode("ascii")
    b_nomeIndice = nomeIndice.encode("ascii")
    b_user_input = user_input.encode("ascii")

    lib.func5POO.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p]
    ret =lib.func5POO(b_nomeArqDados, b_nomeIndice, 1, b_user_input)
    return ret

if __name__ == "__main__":
    listagemRegistros("binario3.bin")
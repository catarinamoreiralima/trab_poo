import ctypes

# load c lib
testlib = ctypes.CDLL('./testlib.so')

def basicTest():
    # teste de print uma string
    string1 = "Hello World!"
    b_string1 = string1.encode("ascii")
    testlib.helloWorld.argtypes = [ctypes.c_char_p]
    testlib.helloWorld(b_string1)

    testlib.printNumber(42)

    print(testlib.returnAddition(2, 3))

def buscaTest():

    b1 = "@|12|marcos|@|palmeiras$asd"
    b_b1 = b1.encode("ascii")
    testlib.buscaHandler.argtypes = [ctypes.c_char_p]
    testlib.buscaHandler(b_b1)




def main():
    # Code to be executed when the script is run directly
    # basicTest()
    buscaTest()
    

if __name__ == "__main__":
    main()
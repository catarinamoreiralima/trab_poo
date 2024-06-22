all:
	gcc *.c *.h -o main

library:
	gcc -shared -fPIC -o lib.so *.c *.h

run: 
	./main

debug:
	gcc *.c *.h -s main


zip:
	zip trab1.zip *.c *.h Makefile
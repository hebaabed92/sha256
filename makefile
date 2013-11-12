sha256i: sha256.o ; gcc sha256.o -o sha256i

sha256.o: sha256.c ; gcc -c sha256.c -o sha256.o

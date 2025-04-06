#Este es el archivo de makefile para kubo.c

kubo.exe: kubo.o funKubo.o
	gcc kubo.o funKubo.o -o kubo.exe

funKubo.o: funKubo.c defKubo.h
	gcc -c funKubo.c

kubo.o: kubo.c defKubo.h
	gcc -c kubo.c
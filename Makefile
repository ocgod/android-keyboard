all:main.c main.h key.h
	g++ -o akb main.c
clean:
	rm -f akb
	

all:main.c main.h cmd.h
	g++ -o akb main.c
clean:
	rm -f akb
	

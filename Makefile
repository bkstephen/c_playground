CC = gcc
CFLAGS_LIBS = `pkg-config --cflags --libs gtk4`
UTILS_LIB_PATHS = nmap 

all: clean pentestapp

pentestapp: shell_utils.o main.o
	${CC} -Wall shell_utils.o main.o -o pentestapp ${CFLAGS_LIBS}

shell_utils.o: shell_utils.c
	${CC} -c shell_utils.c ${CFLAGS_LIBS}

main.o: main.c
	${CC} -c main.c ${CFLAGS_LIBS}

clean:
	rm -f *.o pentestapp

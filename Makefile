CC = gcc
CFLAGS_LIBS = `pkg-config --cflags --libs gtk4`
all:
	${CC} -Wall main.c -o pentestapp ${CFLAGS_LIBS}
clean:
	rm -f pentestapp

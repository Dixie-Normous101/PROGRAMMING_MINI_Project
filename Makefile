CC = clang
CFLAGS = -std=c11 -Wall -Wextra -pedantic

app: main.c menu.c
	$(CC) $(CFLAGS) main.c menu.c -o app

run: app
	./app

clean:
	rm -f app
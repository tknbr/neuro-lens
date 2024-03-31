CC=gcc
CFLAGS=-Iinclude
DEPS =
OBJ = src/main.o
BIN = bin/neuro-lens

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f src/*.o bin/* 

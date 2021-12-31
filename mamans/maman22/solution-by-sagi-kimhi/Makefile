CC=gcc
CFLAGS=-ansi -pedantic -Wall -g
LIBS=-lm
SRC=src
OBJ=obj
HDRS=$(wildcard $(SRC)/*.h)
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BIN=complex

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC):
	mkdir src
	mv *.c ./src
	mv *.h ./src

$(OBJ):
	mkdir obj

clean:
	$(RM) -rf $(OBJ)/* $(BIN)

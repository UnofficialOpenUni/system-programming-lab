CC=gcc
CFLAGS=-ansi -pedantic -Wall -g
SRC=src
OBJ=obj
HDRS=$(wildcard *.h)
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BIN=MagicSquareGen

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r *.o $(BIN) GenFile.txt
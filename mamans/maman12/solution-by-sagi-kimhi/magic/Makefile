CC=gcc
CFLAGS=-ansi -pedantic -Wall -g
SRC=src
OBJ=obj
HEAD=$(wildcard *.h)
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BIN=magic
SUBMITNAME=maman12-sagi-kimhi.zip

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c $(HEAD)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir $@

$(SRC):
	mkdir $@

clean:
	$(RM) -r $(OBJ)/* $(BIN)

submit:
	$(RM) $(SUBMITNAME)
	zip $(SUBMITNAME) * tests/* results/*

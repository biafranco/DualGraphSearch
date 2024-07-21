CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o 

EXE = $(BIN)/main.out

all: $(EXE)

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CC) $(CFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

$(BIN)/main.out: $(OBJS)
	$(CC) -g $(OBJS) $(LIBS) -o $(BIN)/main.out
	
clean:
	rm -f $(EXE) $(OBJS)

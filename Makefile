CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
CFLAGS = -I$(INC)
OBJS = $(OBJ)/main.o $(OBJ)/graph.o $(OBJ)/priority_queue.o $(OBJ)/algorithms.o

EXE = $(BIN)/main.out

all: $(EXE)

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/graph.hpp $(INC)/priority_queue.hpp $(INC)/algorithms.hpp
	$(CC) $(CFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

$(OBJ)/graph.o: $(SRC)/graph.cpp $(INC)/graph.hpp
	$(CC) $(CFLAGS) -c $(SRC)/graph.cpp -o $(OBJ)/graph.o

$(OBJ)/priority_queue.o: $(SRC)/priority_queue.cpp $(INC)/priority_queue.hpp
	$(CC) $(CFLAGS) -c $(SRC)/priority_queue.cpp -o $(OBJ)/priority_queue.o

$(OBJ)/algorithms.o: $(SRC)/algorithms.cpp $(INC)/algorithms.hpp
	$(CC) $(CFLAGS) -c $(SRC)/algorithms.cpp -o $(OBJ)/algorithms.o

$(BIN)/main.out: $(OBJS)
	$(CC) -g $(OBJS) $(LIBS) -o $(BIN)/main.out

clean:
	rm -f $(EXE) $(OBJS)

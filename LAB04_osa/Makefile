# Compilador e flags
CC = g++
CFLAGS = -Wall -g -std=c++11

# Nome do executável
TARGET = projeto_lab04

# Arquivos fonte e objetos
SRCS = Book.cpp BSTree.cpp BSTreeNode.cpp FileManager.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

# Regra principal
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Regra para arquivos objeto
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Regra clean
clean:
	rm -f $(OBJS) $(TARGET)

# Dependências
Book.o: Book.cpp Book.h
BSTree.o: BSTree.cpp BSTree.h BSTreeNode.h
BSTreeNode.o: BSTreeNode.cpp BSTreeNode.h
FileManager.o: FileManager.cpp FileManager.h Book.h BSTree.h IndexEntry.h
main.o: main.cpp FileManager.h

# Regra para reconstruir tudo
all: clean $(TARGET)
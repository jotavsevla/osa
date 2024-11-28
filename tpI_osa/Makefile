# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -Wall -Wextra

# Nome do executável
EXEC = main

# Arquivos fonte
SOURCES = main.cpp

# Arquivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Regra principal
all: $(EXEC)

# Linking
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

# Compilação
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(OBJECTS) $(EXEC)

# Regra para executar o programa
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
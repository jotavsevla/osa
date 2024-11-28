#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <cstring>

using namespace std;

class Registro {
public:
    string nome;
    int idade;
    static const int TAM_NOME = 50;

    Registro() : idade(0) {}
    Registro(const string& n, int i) : nome(n), idade(i) {}

    string packing() const {
        string buffer(TAM_NOME + sizeof(int), '\0');

        string tempNome = nome;
        tempNome.resize(TAM_NOME, '\0');
        memcpy(&buffer[0], tempNome.c_str(), TAM_NOME);

        memcpy(&buffer[TAM_NOME], &idade, sizeof(int));

        return buffer;
    }

    void unpacking(const string& buffer) {
        nome = buffer.substr(0, TAM_NOME);
        nome = nome.c_str();

        memcpy(&idade, &buffer[TAM_NOME], sizeof(int));
    }
};

#endif
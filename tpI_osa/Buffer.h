//
// Created by João on 05/11/24.
//
#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <fstream>
#include <string>
#include "Registro.h"

class Buffer {
public:
    std::fstream& stream;

    Buffer(std::fstream& fs) : stream(fs) {}

    // Lê um registro do arquivo
    std::string lerRegistro() {
        std::string buffer(Registro::TAM_NOME + sizeof(int), '\0');
        stream.read(reinterpret_cast<char*>(&buffer[0]), Registro::TAM_NOME + sizeof(int));
        return buffer;
    }

    // Escreve um registro no arquivo
    void escreverRegistro(const std::string& buffer) {
        stream.write(buffer.c_str(), Registro::TAM_NOME + sizeof(int));
    }
};

#endif
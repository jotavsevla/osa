#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Registro.h"
#include "Buffer.h"

using namespace std;

class Arquivo {
public:
    string nomeArquivo;
    fstream stream;
    Buffer buffer;

    explicit Arquivo(const string& nome) : nomeArquivo(nome), buffer(stream) {
        // Verifica se o arquivo de entrada existe
        ifstream verificaArquivo(nomeArquivo);
        if (!verificaArquivo.is_open()) {
            cerr << "Erro: Arquivo " << nomeArquivo << " não encontrado!" << endl;
            exit(1);
        }
        verificaArquivo.close();
    }

    vector<Registro> lerCSV() {
        vector<Registro> registros;
        ifstream arquivo(nomeArquivo);
        string linha;

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string nome;
            string idade_str;

            getline(ss, nome, ',');
            getline(ss, idade_str);

            try {
                registros.push_back(Registro(nome, stoi(idade_str)));
            } catch (const exception& e) {
                cerr << "Erro ao ler linha: " << linha << endl;
                cerr << "Erro: " << e.what() << endl;
            }
        }

        arquivo.close();
        return registros;
    }

    void escreverBinario(const vector<Registro>& registros, const string& arquivoSaida) {
        stream.open(arquivoSaida, ios::out | ios::binary);
        if (!stream) {
            cerr << "Erro ao criar arquivo binário: " << arquivoSaida << endl;
            return;
        }

        for (const auto& reg : registros) {
            string buffer = reg.packing();
            this->buffer.escreverRegistro(buffer);
        }

        stream.close();
        cout << "Arquivo binário criado com sucesso!" << endl;
    }

    vector<Registro> lerBinario(const string& arquivoEntrada) {
        vector<Registro> registros;
        stream.open(arquivoEntrada, ios::in | ios::binary);

        if (!stream) {
            cerr << "Erro ao abrir arquivo binário para leitura: " << arquivoEntrada << endl;
            return registros;
        }

        while (stream.good() && !stream.eof()) {
            string buffer = this->buffer.lerRegistro();
            if (!stream.eof()) {
                Registro reg;
                reg.unpacking(buffer);
                registros.push_back(reg);
            }
        }

        stream.close();
        return registros;
    }
};

#endif
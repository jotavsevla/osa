#include <iostream>
#include "Arquivo.h"

using namespace std;

int main() {
    // Nome do arquivo CSV de entrada (caminho relativo)
    string arquivoEntrada = "./textos/Nomes_Idades_1.csv";
    // Nome do arquivo binário de saída
    string arquivoBinario = "./dados.bin";

    cout << "Iniciando processamento..." << endl;
    cout << "Arquivo de entrada: " << arquivoEntrada << endl;

    // Cria instância da classe Arquivo
    Arquivo arquivo(arquivoEntrada);

    // Lê registros do arquivo CSV
    vector<Registro> registros = arquivo.lerCSV();

    // Imprime registros lidos do CSV
    cout << "\nRegistros lidos do CSV:" << endl;
    for (const auto& reg : registros) {
        cout << "Nome: " << reg.nome << ", Idade: " << reg.idade << endl;
    }

    cout << "\nCriando arquivo binário: " << arquivoBinario << endl;
    // Escreve registros em arquivo binário
    arquivo.escreverBinario(registros, arquivoBinario);

    // Lê registros do arquivo binário recém-criado
    vector<Registro> registrosBin = arquivo.lerBinario(arquivoBinario);

    // Imprime registros lidos do arquivo binário
    cout << "\nRegistros lidos do arquivo binário:" << endl;
    for (const auto& reg : registrosBin) {
        cout << "Nome: " << reg.nome << ", Idade: " << reg.idade << endl;
    }

    return 0;
}
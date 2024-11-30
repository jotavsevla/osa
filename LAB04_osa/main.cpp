#include <iostream>
#include "FileManager.h"

int main() {
    FileManager manager("books.dat", "index.dat");

    try {
        // 1. Criar arquivo principal e índice a partir do CSV
        cout << "Criando arquivos a partir do CSV..." << endl;
        manager.createFromCSV("/Users/jotavsevla/CLionProjects/OSA/LAB04_osa/BooksDataset.csv");
        cout << "Arquivos criados com sucesso!\n" << endl;

        // 2. Demonstrar consultas por ID retornando título
        cout << "=== Consultas por título ===" << endl;
        int ids[] = {105, 203, 82087, 90878};
        for (int id : ids) {
            string title = manager.getTitleById(id);
            cout << "Título do livro " << id << ": " << title << endl;
        }
        cout << endl;

        // 3. Demonstrar consultas por ID retornando autor
        cout << "=== Consultas por autor ===" << endl;
        for (int id : ids) {
            string author = manager.getAuthorById(id);
            cout << "Autor do livro " << id << ": " << author << endl;
        }
        cout << endl;

        // 4. Demonstrar inserção de novos livros e atualização do índice
        cout << "=== Teste de inserção ===" << endl;
        Book newBooks[] = {
                {999997, "Clean Code", "Robert C. Martin", 2008, "Programming,Software Engineering"},
                {999998, "Design Patterns", "Gang of Four", 1994, "Programming,Software Engineering"},
                {999999, "The Pragmatic Programmer", "Andrew Hunt, David Thomas", 1999, "Programming"}
        };

        for (const auto& book : newBooks) {
            manager.insertBook(book);
            cout << "Livro inserido - ID: " << book.id << ", Título: " << book.title << endl;

            // Verificar se foi inserido corretamente
            Book retrieved = manager.getBookById(book.id);
            cout << "Verificação - Título: " << retrieved.title << ", Autor: " << retrieved.authors << endl;
        }

    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        return 1;
    }

    return 0;
}
#include <iostream>
#include "FileManager.h"

int main() {
    FileManager manager("books.dat", "index.dat");

    try {
        // 1. Criar arquivo principal e índice a partir do CSV
        std::cout << "Criando arquivos a partir do CSV..." << std::endl;
        manager.createFromCSV("/Users/jotavsevla/CLionProjects/OSA/LAB04_osa/BooksDataset.csv");
        std::cout << "Arquivos criados com sucesso!\n" << std::endl;

        // 2. Demonstrar consultas por ID retornando título
        std::cout << "=== Consultas por título ===" << std::endl;
        int ids[] = {105, 203, 82087, 90878};
        for (int id : ids) {
            std::string title = manager.getTitleById(id);
            std::cout << "Título do livro " << id << ": " << title << std::endl;
        }
        std::cout << std::endl;

        // 3. Demonstrar consultas por ID retornando autor
        std::cout << "=== Consultas por autor ===" << std::endl;
        for (int id : ids) {
            std::string author = manager.getAuthorById(id);
            std::cout << "Autor do livro " << id << ": " << author << std::endl;
        }
        std::cout << std::endl;

        // 4. Demonstrar inserção de novos livros e atualização do índice
        std::cout << "=== Teste de inserção ===" << std::endl;
        Book newBooks[] = {
                {999997, "Clean Code", "Robert C. Martin", 2008, "Programming,Software Engineering"},
                {999998, "Design Patterns", "Gang of Four", 1994, "Programming,Software Engineering"},
                {999999, "The Pragmatic Programmer", "Andrew Hunt, David Thomas", 1999, "Programming"}
        };

        for (const auto& book : newBooks) {
            manager.insertBook(book);
            std::cout << "Livro inserido - ID: " << book.id << ", Título: " << book.title << std::endl;

            // Verificar se foi inserido corretamente
            Book retrieved = manager.getBookById(book.id);
            std::cout << "Verificação - Título: " << retrieved.title << ", Autor: " << retrieved.authors << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
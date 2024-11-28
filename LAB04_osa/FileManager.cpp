// FileManager.cpp
#include "FileManager.h"
#include <iostream>

FileManager::FileManager(const std::string& dataPath, const std::string& indexPath)
        : dataFile(dataPath), indexFile(indexPath), root(nullptr) {}

void FileManager::insertNode(BSTreeNode*& node, IndexEntry entry) {
    if (!node) {
        node = new BSTreeNode(entry);
        return;
    }

    if (entry.id < node->data.id)
        insertNode(node->left, entry);
    else
        insertNode(node->right, entry);
}

BSTreeNode* FileManager::search(BSTreeNode* node, int id) {
    if (!node || node->data.id == id)
        return node;

    if (id < node->data.id)
        return search(node->left, id);
    return search(node->right, id);
}

void FileManager::createFromCSV(const std::string& csvPath) {
    std::ifstream csvFile(csvPath);
    if (!csvFile.is_open()) {
        throw std::runtime_error("Could not open CSV file");
    }

    std::ofstream outFile(dataFile, std::ios::binary);
    std::ofstream idxFile(indexFile, std::ios::binary);

    std::string line;
    std::getline(csvFile, line); // Skip header

    while (std::getline(csvFile, line)) {
        try {
            Book book;
            std::stringstream ss(line);
            std::string token;

            // ID
            if (!std::getline(ss, token, ';')) continue;
            if (token.empty()) continue;
            book.id = std::stoi(token);

            // Title
            if (!std::getline(ss, book.title, ';')) continue;

            // Authors
            if (!std::getline(ss, book.authors, ';')) continue;

            // Year
            if (!std::getline(ss, token, ';')) continue;
            if (token.empty() || token == "") {
                book.year = 0;
            } else {
                try {
                    book.year = std::stoi(token);
                } catch (...) {
                    book.year = 0;
                }
            }

            // Categories
            std::getline(ss, book.categories);

            // Write to files
            long position = outFile.tellp();
            std::string packed = book.pack();
            outFile.write(packed.c_str(), packed.length());

            IndexEntry entry{book.id, position};
            insertNode(root, entry);

            idxFile.write(reinterpret_cast<char*>(&entry), sizeof(IndexEntry));
        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << "\n";
            continue;
        }
    }

    csvFile.close();
    outFile.close();
    idxFile.close();
}

Book FileManager::getBookById(int id) {
    BSTreeNode* node = search(root, id);
    if (!node) throw std::runtime_error("Book not found");

    std::ifstream file(dataFile, std::ios::binary);
    file.seekg(node->data.position);

    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(int));

    std::string buffer;
    buffer.resize(size);
    file.read(&buffer[0], size);

    Book book;
    book.unpack(buffer);
    return book;
}

void FileManager::insertBook(const Book& book) {
    std::ofstream outFile(dataFile, std::ios::binary | std::ios::app);

    long position = outFile.tellp();
    std::string packed = book.pack();
    outFile.write(packed.c_str(), packed.length());

    IndexEntry entry{book.id, position};
    insertNode(root, entry);

    saveIndexToFile();
    outFile.close();
}

std::string FileManager::getTitleById(int id) {
    try {
        Book book = getBookById(id);
        return book.title;
    } catch (const std::exception& e) {
        return "Book not found";
    }
}

std::string FileManager::getAuthorById(int id) {
    try {
        Book book = getBookById(id);
        return book.authors;
    } catch (const std::exception& e) {
        return "Book not found";
    }
}

void FileManager::loadIndexFromFile() {
    std::ifstream idxFile(indexFile, std::ios::binary);
    if (!idxFile) return;

    IndexEntry entry;
    while (idxFile.read(reinterpret_cast<char*>(&entry), sizeof(IndexEntry))) {
        insertNode(root, entry);
    }
    idxFile.close();
}

void FileManager::saveIndexToFile() {
    std::ofstream idxFile(indexFile, std::ios::binary);
    if (!idxFile) return;

    std::function<void(BSTreeNode*)> inorderTraversal = [&](BSTreeNode* node) {
        if (!node) return;
        inorderTraversal(node->left);
        idxFile.write(reinterpret_cast<char*>(&node->data), sizeof(IndexEntry));
        inorderTraversal(node->right);
    };

    inorderTraversal(root);
    idxFile.close();
}


void deleteTree(BSTreeNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

FileManager::~FileManager() {
    deleteTree(root);
}

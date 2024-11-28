// FileManager.h
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include "Book.h"
#include "BSTree.h"

class FileManager {
private:
    std::string dataFile;
    std::string indexFile;
    BSTreeNode* root;

    void insertNode(BSTreeNode*& node, IndexEntry entry);
    BSTreeNode* search(BSTreeNode* node, int id);

public:
    FileManager(const std::string& dataPath, const std::string& indexPath);
    void createFromCSV(const std::string& csvPath);
    Book getBookById(int id);
    std::string getTitleById(int id);
    std::string getAuthorById(int id);
    void loadIndexFromFile();
    void saveIndexToFile();
    void insertBook(const Book& book);
    ~FileManager();
};

#endif

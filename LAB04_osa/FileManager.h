// FileManager.h
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include "Book.h"
#include "BSTree.h"

class FileManager {
private:
    string dataFile;
    string indexFile;
    BSTreeNode* root;

    void insertNode(BSTreeNode*& node, IndexEntry entry);
    BSTreeNode* search(BSTreeNode* node, int id);
    void traverseAndSave(BSTreeNode* node, ofstream& idxFile);

public:
    FileManager(const string& dataPath, const string& indexPath);
    void createFromCSV(const string& csvPath);
    Book getBookById(int id);
    string getTitleById(int id);
    string getAuthorById(int id);
    void loadIndexFromFile();
    void saveIndexToFile();
    void insertBook(const Book& book);
    ~FileManager();
};

#endif

// Book.h
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <sstream>
#include <cstring>

using namespace std;

class Book {
public:
    int id;
    string title;
    string authors;
    int year;
    string categories;

    string pack() const;
    bool unpack(const string& buffer);
};

#endif
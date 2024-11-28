// Book.h
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <sstream>
#include <cstring>

class Book {
public:
    int id;
    std::string title;
    std::string authors;
    int year;
    std::string categories;

    std::string pack() const;
    bool unpack(const std::string& buffer);
};

#endif
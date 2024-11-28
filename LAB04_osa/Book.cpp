// Book.cpp
#include "Book.h"

std::string Book::pack() const {
    std::string data = std::to_string(id) + "|" + title + "|" + authors + "|" +
                       std::to_string(year) + "|" + categories;
    int size = data.length() + sizeof(int);

    std::string buffer;
    buffer.resize(sizeof(int));
    memcpy(&buffer[0], &size, sizeof(int));
    buffer += data;

    return buffer;
}

bool Book::unpack(const std::string& buffer) {
    if (buffer.size() < sizeof(int)) return false;

    int size;
    memcpy(&size, buffer.data(), sizeof(int));

    std::string data = buffer.substr(sizeof(int));
    std::stringstream ss(data);
    std::string idStr, yearStr;

    std::getline(ss, idStr, '|');
    std::getline(ss, title, '|');
    std::getline(ss, authors, '|');
    std::getline(ss, yearStr, '|');
    std::getline(ss, categories);

    try {
        id = std::stoi(idStr);
        year = std::stoi(yearStr);
    } catch (const std::exception& e) {
        return false;
    }

    return true;
}

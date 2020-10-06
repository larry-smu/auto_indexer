//
// Created by Larry Yu on 9/29/20.
//

#include "subEntry.h"

subEntry::subEntry() {

}

subEntry::subEntry(const subEntry &s) {
    word = s.word;

    parent = s.parent;

    DSVector<int> sv = s.page_number;
    for(int i = 0; i < sv.getLength(); ++i) {
        page_number.append(sv.at(i));
    }
}

subEntry::~subEntry() {

}

void subEntry::setString(char *str) {
    word = str;
}

void subEntry::setString(DSString s) {
    word = s;
}

DSString subEntry::getWord() {
    return word;
}

void subEntry::setParent(const DSString& s) {
    parent = s;
}

DSString subEntry::getParent() {
    return parent;
}


void subEntry::addPageNumber(int pageNum) {
    page_number.append(pageNum);
}

void subEntry::sortPageNumber() {
    page_number.sort();
}

DSVector<int> subEntry::getPageNumber() {
    return page_number;
}


void subEntry::print() {
    word.print();
    std::cout << ": ";
    for(int i = 0; i < page_number.getLength(); ++i) {
        std::cout << page_number.at(i) << " ";
    }
    std::cout << std::endl;
}
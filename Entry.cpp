#include "Entry.h"

/**
 * Rule of 3
 */
Entry::Entry() {

};

Entry::Entry(const Entry& e) {
    word = e.word;

    DSVector<int> e_p = e.page_number;
    DSVector<Entry*> e_s = e.sub;

    for(int i = 0; i < e_p.getLength(); ++i) {
        page_number.append(e_p.at(i));
    }

    for(int i =0; i < e_s.getLength(); ++i) {
        sub.append(e_s.at(i));
    }
}

Entry::~Entry() {

}

/**
 * Functions
 **/
void Entry::setString(char *str) {
    word = str;
}

void Entry::setString(DSString s) {
    word = s;
}

DSString Entry::getWord() {
    return word;
}

void Entry::addPageNumber(int pageNum) {
    page_number.append(pageNum);
    page_number.sort();
}

DSVector<int> Entry::getPageNumber() {
    return page_number;
}

void Entry::addSub(Entry* e) {
    sub.append(e);
}

DSVector<Entry*> Entry::getSub() {
    return sub;
}

void Entry::print() {
    word.print();
    std::cout << ": ";
    for(int i = 0; i < page_number.getLength(); ++i) {
        if(i == page_number.getLength()-1)
            std::cout << page_number.at(i) << " ";
        else
            std::cout << page_number.at(i) << ", ";
    }

    for (int i = 0; i < sub.getLength(); ++i) {
        if(i == 0)
            std::cout << std::endl << "  ";
        else
            std::cout << "  ";
        Entry* se = sub.at(i);
        se->print();
    }
    std::cout << std::endl;
}

bool Entry::operator<(const Entry& e) {
    return this->word < e.word;
}




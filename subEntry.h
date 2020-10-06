//
// Created by Larry Yu on 9/29/20.
//

#ifndef INC_20F_AUTO_IDX_SUBENTRY_H
#define INC_20F_AUTO_IDX_SUBENTRY_H

#include "DSVector.h"
#include "DSList.h"
#include "DSString.h"

class subEntry {
private:
    DSString word;
    DSString parent;
    DSVector<int> page_number;

public:
    subEntry();
    subEntry(const subEntry&);
    ~subEntry();

    void setString(char*);
    void setString(DSString);
    DSString getWord();
    void setParent(const DSString&);
    DSString getParent();
    void addPageNumber(int);
    void sortPageNumber();
    DSVector<int> getPageNumber();
    void print();
};


#endif //INC_20F_AUTO_IDX_SUBENTRY_H

#ifndef INC_20F_AUTO_IDX_ENTRY_H
#define INC_20F_AUTO_IDX_ENTRY_H

#include "DSVector.h"
#include "DSList.h"
#include "DSString.h"
#include "subEntry.h"

#include <fstream>

class Entry {
private:
    DSString word;
    DSVector<int> page_number;
    DSVector<Entry*> sub;

public:
    /**
     * Rule of 3
     */
     Entry();
     Entry(const Entry&);
     ~Entry();

    /**
     * Functions
     */
    void setString(char*);
    void setString(DSString);
    DSString getWord();
    void addPageNumber(int);
    DSVector<int> getPageNumber();
    void addSub(Entry*);
    void print();
    DSVector<Entry*> getSub();

    bool operator< (const Entry&);

    void writeToFile(char*);
};


#endif //INC_20F_AUTO_IDX_ENTRY_H

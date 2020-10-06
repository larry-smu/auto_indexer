#ifndef INC_20F_AUTO_IDX_INDEX_H
#define INC_20F_AUTO_IDX_INDEX_H

#include <iostream>
#include <fstream>
#include <typeinfo>

#include "Entry.h"
#include "DSVector.h"
#include "DSList.h"
#include "DSString.h"
#include "subEntry.h"

class Index {
private:
    DSList<Entry> index;

public:
    /**
     * Rule of 3
     */
    Index();
    Index(const Index&);
    ~Index();

    /**
     * Functions
     */
    void readFile(char*);
    DSList<Entry> getIndex();
    Entry createEntry(DSString, int);
    DSString createWord(int &count_index, int &count_char, const char *line, DSString temp_str);
    Entry createEntry(DSString word, Entry& se);
    int checkEntryExist(DSString s);
    void sort();
    void print();

    void writeToFile(char*);

    void writeEntry(Entry e, DSString word, std::ofstream& os);
};


#endif //INC_20F_AUTO_IDX_INDEX_H
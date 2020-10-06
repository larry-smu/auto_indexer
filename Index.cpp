#include "Index.h"

/**
 * Rule of 3
 */
Index::Index() {

}

Index::Index(const Index& index) {
    DSList<Entry> in = index.index;
    for(int i = 0; i < in.getLength(); ++i) {
        this->index.push_back(in.at(i));
    }
}

Index::~Index() {

}

/**
 * Functions
 */

DSList<Entry> Index::getIndex() {
    return index;
}

DSString Index::createWord(int &count_index, int &count_char, const char line[], DSString temp_str) {
    //Append chars to temp_str
    for(int i = count_index; i <= count_char+count_index-1; ++i) {
        //Set word
        if(line[i] != '[' && line[i] != ']') {
            int length = temp_str.getLength();
            char *r = new char[length + 2];
            strcpy(r, temp_str.c_str());
            r[length] = line[i];
            r[length + 1] = '\0';
            temp_str = r;
            delete[] r;
        }
    }

    count_index += count_char; //Add the number of char to count_index
    ++count_index; //Add one because of space between word
    count_char = 0; //Reset count_char

    temp_str.remove_end_punctuation(); //Remove punctuation if any
    temp_str.toLowerCase(); //Set all char to lowercase

    return temp_str;
}


Entry Index::createEntry(DSString word, int page_number) {
    Entry e;
    e.setString(word);
    e.addPageNumber(page_number);
    return e;
}

Entry Index::createEntry(DSString word, Entry& se) {
    Entry e;
    e.setString(word);
    e.addSub(&se);
    return e;
}

int Index::checkEntryExist(DSString s) {
    for(int i = 0; i < index.getLength(); ++i) {
        Entry comp = index.at(i);
        DSString comp_str = comp.getWord();
        if(strcmp(s.c_str(), comp_str.c_str()) == 0)
            return i;
    }
    return -1;
}

void Index::sort() {
    index.sort();
}

void Index::print() {
    std::cout << index.getLength() << std::endl;
    std::cout << "PRINTING" << std::endl;

    char alphabet = ' ';
    for(int i = 0; i < index.getLength(); ++i) {
        Entry e = index.at(i);
        DSString word = e.getWord();
        if(alphabet != word.getAlphabet()) {
            alphabet = word.getAlphabet();
            std::cout << "[" << alphabet << "]" << std::endl;
        }
        e.print();
    }
}

void Index::writeEntry(Entry e, DSString word, std::ofstream& os) {
    DSVector<int> page_number = e.getPageNumber();

    os << word << ": ";
    for(int i = 0; i < page_number.getLength(); ++i) {
        if(i == page_number.getLength()-1)
            os << page_number.at(i) << " ";
        else
            os << page_number.at(i) << ", ";
    }
}

void Index::writeToFile(char* filename) {

    std::cout << "WRITING TO FILE" << std::endl;
    std::ofstream os(filename);
    char alphabet = ' ';
    for(int i = 0; i < index.getLength(); ++i) {
        Entry e = index.at(i);
        DSString word = e.getWord();
        if(alphabet != word.getAlphabet()) {
            alphabet = word.getAlphabet();
            os << "[" << alphabet << "]" << std::endl;
        }

        writeEntry(e, word, os);

        DSVector<Entry*> sub = e.getSub();
        for (int i = 0; i < sub.getLength(); ++i) {
            if(i == 0)
                os << std::endl << "  ";
            else
                os << "  ";

            Entry* se = sub.at(i);
            DSString word = se->getWord();
            writeEntry(*se, word, os);
            os << std::endl;
        }
        os << std::endl;
    }
}

void Index::readFile(char* filename) {

    //Read File
    std::ifstream file(filename);

    std::cout << "READING FILE" << std::endl << std::endl;
    
    char line[40];
    int withBracket = 0;
    Index in;


    DSList<Entry> results;
    DSList<subEntry> subs;

    if (file.is_open()) {

        DSString page_number;
        int p;

        while (file.getline(line, 40)) {
            DSString temp = line;
            DSString temp_str;

            int count_char = 0; //Count the number of char in a word
            int count_index = 0; //Count the index for char word

            /**
             * IF: The line starts with '<', set the page number
             * ELSE: Get the word, store in a map with page number
             */
            if (line[0] == '<') {
                page_number = line;
                page_number.remove_bracket();
                p = atoi(page_number.c_str());
                temp.empty_str();
                if(p == -1) break;
            } else {
                for (int i = 0; i < temp.getLength(); ++i) {
                    //If there is a space, temp_str is a word
                    if (line[i] == ' ' && withBracket == 0) {

                        temp_str = in.createWord(count_index, count_char, line, temp_str); //Create the word

                        //CHECK IF THE WORD EXIST IN INDEX
                        int existIndex = checkEntryExist(temp_str.getChild());
                        if( existIndex != -1) {
                            Entry& existEntry = index.at(existIndex);
                            existEntry.addPageNumber(p);
                        } else {
                            Entry e = createEntry(temp_str.getChild(), p);
                            index.push_back(e);
                        }

                        index.sort(); //Sort the index

                        //if the word is a sub word, append to sub
                        if(temp_str.isSub()) {
                            subEntry se;
                            se.setParent(temp_str.getParent());
                            se.setString(temp_str.getChild());
                            subs.push_back(se);
                        }

                        temp_str.empty_str(); //Empty the temp_str for new word
                    }
                    //Else is not a word, unless at the end of the line
                    else {
                        if (line[i] == '[')
                            withBracket = 1;

                        if (line[i + 1] == ']')
                            withBracket = 0;

                        ++count_char; //If line[i] is not a space, +1 to count_char

                        //End of the line so it is a word
                        if (count_char + count_index == temp.getLength()) {


                            temp_str = in.createWord(count_index, count_char, line, temp_str); //Create the word

                            //CHECK IF THE WORD EXIST IN INDEX
                            int existIndex = checkEntryExist(temp_str.getChild());
                            if( existIndex != -1) {
                                Entry& existEntry = index.at(existIndex);
                                existEntry.addPageNumber(p);
                            } else {
                                Entry e = createEntry(temp_str.getChild(), p);
                                index.push_back(e);
                            }

                            index.sort(); //Sort index

                            //if the word is a sub word, append to sub
                            if(temp_str.isSub()) {
                                subEntry se;
                                DSString parent = temp_str.getParent();
                                se.setParent(parent);
                                se.setString(temp_str.getChild());
                                subs.push_back(se);
                            }
                        }
                    }
                }
            }
        }

        /**
         * Loop through all the subwords in DSList,
         * and append the memory address of the word to its parents' sub vector
         */
        for(int i = 0; i < subs.getLength(); ++i) {
            subEntry sub_entry = subs.at(i);
            DSString parent = sub_entry.getParent();
            DSString child = sub_entry.getWord();
            int existIndex = checkEntryExist(child);
            int checkIfParentExist = checkEntryExist(parent);
            int existParentIndex = checkEntryExist(parent);
            if(checkIfParentExist != -1) {
                Entry& existEntry = index.at(existParentIndex);
                existEntry.addSub(&index.at(existIndex));
            } else {
                Entry parentEntry = createEntry(parent, index.at(existIndex));
                index.push_back(parentEntry);
            }
        }

    } else {
        std::perror(filename);
    }
}
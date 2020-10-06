#ifndef INC_20F_AUTO_IDX_DSSTRING_H
#define INC_20F_AUTO_IDX_DSSTRING_H

#include <iostream>
#include <cstring>
#include <cctype>

class DSString {
private:
    char* str;

public:
    DSString();
    DSString(const char*);
    DSString(const DSString &);
    ~DSString();

    //Functions
    int getLength();
    void print();
    void append(char*);
    DSString substring(int start, int numChars);
    void toLowerCase();
    void remove_end_punctuation();
    void remove_bracket();
    void empty_str();
    void pop();
    bool isSub();
    DSString getParent();
    DSString getChild();

    //Operators
    DSString& operator= (const char*);
    DSString& operator= (const DSString&);
    DSString operator+ (DSString&);
    DSString& operator+= (const DSString&);
    bool operator== (const char*);
    bool operator== (const DSString&);
    bool operator> (const DSString&);
    bool operator< (const DSString&);
    char& operator[] (const int);

    /**
    * Overloaded stream insertion operator to print the contents of this
    * string to the output stream in the first argument.
    **/
    friend std::ostream& operator<< (std::ostream& os, const DSString& s) {
        if(strlen(s.str) > 0) {
            for(int i = 0; i < strlen(s.str); i++) {
                os << s.str[i];
            }
        } else {
            os << "";
        }
        return os;
    };

    /**
     * the c_str function returns a null-terminated c-string holding the
     * contents of this object.
     **/
    char* c_str();


    char getAlphabet();

    void setString(const DSString &data);
};


#endif //INC_20F_AUTO_IDX_DSSTRING_H

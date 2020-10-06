#include "DSString.h"

/**
 * Rule of Three
 **/

DSString::DSString() {
    str = new char[1];
    str[0] = '\0';
}

DSString::DSString(const char *data) {
    int l = strlen(data);
    str = new char[l + 1];
    for(int i = 0; i < l+1; ++i) {
        this->str[i] = data[i];
    }


//    strcpy(str, data);
}

DSString::DSString(const DSString &data) {
    this->str = new char[strlen(data.str) + 1];
    for(int i = 0; i < strlen(data.str) + 1; ++i) {
        this->str[i] = data.str[i];
    }
//    strcpy(this->str, data.str);
}

DSString::~DSString() {
    delete[] str;
}


/**
 * Functions
 **/

//Set
void DSString::setString(const DSString &data) {
    *this = data;
}

//Return Length
int DSString::getLength() {
    int len = strlen(str);
    return len;
}

//Print String
void DSString::print() {
    for(int i = 0; i < strlen(str); ++i) {
        std::cout << str[i];
    }
}

//Adding more character
void DSString::append(char* c) {
    int len = strlen(str)+strlen(c)+1;
    char * newArray = new char[len];
    newArray[strlen(newArray)-1] = '\0';

    for(int i = 0; i < strlen(str) + 1; ++i) {
        newArray[i] = str[i];
    }

//    strcpy(newArray,str);
    strcat(newArray,c);

    for(int i = 0; i < len; ++i) {
        str[i] = newArray[i];
    }
//    strcpy(str, newArray);
    delete[] newArray;
}

//Getting substring
DSString DSString::substring(int start, int numChars) {
    DSString new_str;
    for(int i = start; i < start + numChars; ++i) {
        new_str.append(&str[i]);
    }
    return new_str;
}

//Lower case all char
void DSString::toLowerCase() {
    for(int i = 0; i < strlen(str); ++i) {
        str[i] = tolower(str[i]);
    }
}

//Remove punctuation from at the end
void DSString::remove_end_punctuation() {
    while(ispunct(str[-1])) {
        str[-1] = '\0';
    }
    str[strlen(str)] = '\0';
}

//Remove bracket
void DSString::remove_bracket() {
    char *t = this->str;
    t++;
    for(int i = 0; i < strlen(t); ++i) {
        if(t[i] == '>') {
            t[i] = '\0';
        }
    }
    *this = t;
}

void DSString::empty_str() {
    int l = strlen(str);
    memset(str, 0, l);
}

void DSString::pop() {
    str[strlen(str) - 1] = '\0';
}

bool DSString::isSub() {
    for(int i = 0; i < strlen(str); ++i) {
        if(str[i] == '(')
            return true;
    }
    return false;
}

DSString DSString::getParent() {
    DSString temp;
    temp.empty_str();

    int p = 0;
    int l = strlen(str);
    for (int i = 0; i < l; ++i) {
        ++p;
        if (str[i] == '(')
            break;
    }

    for (int i = p; i < l; ++i) {
        if (str[i] != '(' && str[i] != ')') {
            int length = temp.getLength();
            char *r = new char[length + 2];

            for(int j = 0; j < temp.getLength(); ++j) {
                char *t = temp.c_str();
                r[j] = t[j];
            }
//            strcpy(r, temp.c_str());
            r[length] = str[i];
            r[length + 1] = '\0';
            temp = r;
            delete[] r;
        }
    }

    return temp;
}

DSString DSString::getChild() {
    DSString re;
    re.empty_str();
    int p = 0;
    int l = strlen(str);
    for(int i = 0; i < l; ++i) {
        if(str[i] == '(')
            p = 1;
        if(p == 0 && (str[i] != '(' || str[i] != ')')) {
            int length = re.getLength();
            char *r = new char[length + 2];

            for(int j = 0; j < re.getLength(); ++j) {
                char *t = re.c_str();
                r[j] = t[j];
            }

//            strcpy(r, re.c_str());
            r[length] = str[i];
            r[length + 1] = '\0';
            re = r;
            delete[] r;
        }
    }
    return re;
}

char DSString::getAlphabet() {
    return str[0];
}

char* DSString::c_str() {
    return str;
}

/**
 * Operators
 **/

DSString& DSString::operator= (const char * c) {
    if(str == c)
        return *this;

    delete[] str;
    str = new char[strlen(c) + 1];


    for(int i = 0; i < strlen(c)+1; ++i) {
        this->str[i] = c[i];
    }

//    strcpy(str, c);
    str[strlen(str)] = '\0';
    return *this;
}

DSString& DSString::operator= (const DSString& s) {
    if(str == s.str)
        return *this;

    delete[] str;
    str = new char[strlen(s.str) + 1];

    for(int i = 0; i < strlen(s.str) +1; ++i) {
        this->str[i] = s.str[i];
    }

//    strcpy(str, s.str);
    str[strlen(str)] = '\0';
    return *this;
}

DSString& DSString::operator+= (const DSString& s) {
    char* new_str = new char[strlen(str) + strlen(s.str)];

    int j = 0;
    for(int i = 0; i < strlen(new_str); ++i) {
        if(i < strlen(str)) {
            new_str[i] = str[i];
            continue;
        }
        new_str[i] = s.str[j];
        ++j;
    }

    str[strlen(str)] = '\0';

    delete[]  new_str;

    return *this;
}

DSString DSString::operator+ (DSString& s) {
    return (*this += s);
}

bool DSString::operator== (const char* c) {
    return *str == *c;
}

bool DSString::operator== (const DSString& s) {
    return *str == *s.str;
}

bool DSString::operator> (const DSString& s) {
    return *str > *s.str;
}

bool DSString::operator< (const DSString& s) {
    return *str < *s.str;
}

char& DSString::operator[] (const int i) {
    return str[i];
}
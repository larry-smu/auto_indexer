#ifndef S20_PA01_SENTIMENTANALYSIS_TEST_H
#define S20_PA01_SENTIMENTANALYSIS_TEST_H

#include "catch.hpp"
#include "DSString.h"
#include "DSList.h"
#include "DSVector.h"

TEST_CASE("DSString Test Case") {

    //Declare strings for testing
    DSString a;
    DSString b("String B");
    DSString c("String C");
    DSString d("This is Last String");
    DSString e("Just Kidding");
    DSString f("A!");
    DSString g("A!!!!!!!!!!!");

    //Testing getLength()
    SECTION("getLength()") {
//        CHECK(a.getLength() == 0);
        CHECK(b.getLength() == 8);
        CHECK(c.getLength() == 8);
        CHECK(d.getLength() == 19);
        CHECK(e.getLength() == 12);
    }

    //Appending more char to the string and see if the length increased by the same amount of char added
    SECTION("append()") {
        b.append((char*)"K");
        CHECK(b.getLength() == 9);
        c.append((char*)"AP");
        CHECK(c.getLength() == 10);
        d.append((char*)"NO");
        CHECK(d.getLength() == 21);
        e.append((char*)"Yes");
        CHECK(e.getLength() == 15);
    }

//Remove the punctuations for DSString f and g, and use strcmp() to check
    SECTION("remove_end_punctuation()") {
        f.remove_end_punctuation();
        CHECK(strcmp(f.c_str(), "A"));
        g.remove_end_punctuation();
        CHECK(strcmp(g.c_str(), "A"));
    }

    //Testing operators
    SECTION("Operators") {
        a = "This is a";
        CHECK((a == "This is a"));
        a += " adding to a";
        CHECK((a == "This is a adding to a"));
        DSString k = "as second";
        a = k;
        CHECK((a == "as second"));
        CHECK((a[1] == 's'));
        CHECK(!(a < k));
        CHECK(!(a > k));
    }
}

TEST_CASE("DSVector Test Case") {

    //Declare some DSVector for testing
    DSVector<int> int_v;
    DSVector<char*> char_v;
    DSVector<DSString> dsstring_v; //Testing vector with DSString

    //Testing append() with getLength()
    SECTION("append() and getLength()") {
        //First check if all vector's length is 0
        CHECK(int_v.getLength() == 0);
        CHECK(char_v.getLength() == 0);
        CHECK(dsstring_v.getLength() == 0);

        //Append 1 element
        int_v.append(0);
        char_v.append((char*)"First index");

        DSString a("DSString for testing DSVector"); // DSString for dsstring_v
        dsstring_v.append(a);

        CHECK(int_v.getLength() == 1);
        CHECK(char_v.getLength() == 1);
        CHECK(dsstring_v.getLength() == 1);

        //Append another element
        int_v.append(1);
        char_v.append((char*)"Second index");
        dsstring_v.append(a);

        CHECK(int_v.getLength() == 2);
        CHECK(char_v.getLength() == 2);
        CHECK(dsstring_v.getLength() == 2);
    }

        //Testing search()
    SECTION("search()") {
        //Declare and append some objects to the vectors for testing
        int_v.append(0);
        int_v.append(1);
        int_v.append(2);
        int_v.append(3);

        char_v.append((char*)"First index");
        char_v.append((char*)"Second index");
        char_v.append((char*)"Third index");
        char_v.append((char*)"Forth index");

        //Testing int vector
        CHECK(int_v.search(0) == 0);
        CHECK(int_v.search(2) == 2);
        CHECK(int_v.search(3) == 3);
        CHECK(int_v.search(10) == -1);

        //Testing char vector
        CHECK(char_v.search((char*)"First index") == 0);
        CHECK(char_v.search((char*)"Second index") == 1);
        CHECK(char_v.search((char*)"Forth index") == 3);
        CHECK(char_v.search((char*)"first index") == -1);
    }

    //Testing at() and operator[]
    SECTION("at() and operator[]") {
        //Appending to list for testing
        int_v.append(0);
        int_v.append(1);
        int_v.append(2);
        int_v.append(3);

        char_v.append((char*)"First index");
        char_v.append((char*)"Second index");
        char_v.append((char*)"Third index");
        char_v.append((char*)"Forth index");

        //Testing int vector
        CHECK(int_v.at(0) == 0);
        CHECK(int_v.at(1) == 1);
        CHECK(int_v.at(3) == 3);
        CHECK(int_v[0] == 0);
        CHECK(int_v[3] == 3);

        //Testing char vector
        CHECK(char_v.at(0) == "First index");
        CHECK(char_v.at(2) == "Third index");
        CHECK(char_v.at(3) == "Forth index");
        CHECK(char_v[0] == "First index");
        CHECK(char_v[3] == "Forth index");

    }

        //Testing isEmpty()
    SECTION("isEmpty()") {
        //All should be empty
        CHECK(int_v.isEmpty());
        CHECK(char_v.isEmpty());
        CHECK(dsstring_v.isEmpty());

        //Append to list
        int_v.append(0);
        char_v.append((char*)"First index");
        DSString a("First");
        dsstring_v.append(a);

        //CHECK if list is not empty
        CHECK(int_v.isEmpty() == 0);
        CHECK(char_v.isEmpty() == 0);
        CHECK(dsstring_v.isEmpty() == 0 );
    }

        //Testing removeElement()
    SECTION("removeElement()") {
        //Appending to list for testing
        int_v.append(0);
        int_v.append(1);
        int_v.append(2);
        int_v.append(3);

        int_v.removeElement(1);
        CHECK(int_v.getLength() == 3);
        int_v.removeElement(0);
        CHECK(int_v.getLength() == 2);
        int_v.removeElement(3);
        CHECK(int_v.getLength() == 1);
    }

        //Testing sorting()
    SECTION("sorting()") {
        //Appending to list for testing
        int_v.append(7);
        int_v.append(3);
        int_v.append(0);
        int_v.append(6);

        //Sort
        int_v.sort();

        CHECK(int_v.at(0) == 0);
        CHECK(int_v.at(1) == 3);
        CHECK(int_v.at(2) == 6);
        CHECK(int_v.at(3) == 7);

    }
}

TEST_CASE("DSList Test Case") {

    //Declare some List for testing
    DSList<int> a;
    DSList<char*> char_l;
    DSList<DSString> dsstring_l;

    //Append some data and test it with the length
    SECTION("push_back() and getLength()") {
        //Testing int DSList
        CHECK(a.getLength() == 0);
        a.push_back(0);
        CHECK(a.getLength() == 1);
        a.push_back(1);
        CHECK(a.getLength() == 2);
        a.push_back(2);
        CHECK(a.getLength() == 3);

        //Testing char* DSList
        CHECK(char_l.getLength() == 0);
        char_l.push_back((char*)"first");
        CHECK(char_l.getLength() == 1);
        char_l.push_back((char*)"second");
        CHECK(char_l.getLength() == 2);

        //Declare some DSString to push_back()
        DSString a("First");
        DSString b("Second");
        DSString c("Third");

        //Testing DSString DSList
        CHECK(dsstring_l.getLength() == 0);
        dsstring_l.push_back(a);
        CHECK(dsstring_l.getLength() == 1);
        dsstring_l.push_back(b);
        CHECK(dsstring_l.getLength() == 2);
        dsstring_l.push_back(c);
        CHECK(dsstring_l.getLength() == 3);
    }

        //Testing search()
    SECTION("search()") {
        //Appending for tests
        a.push_back(0);
        a.push_back(1);
        a.push_back(2);

        char_l.push_back((char*)"first");
        char_l.push_back((char*)"second");
        char_l.push_back((char*)"third");

        //Testing
        CHECK(a.search(0) == 0);
        CHECK(a.search(1) == 1);
        CHECK(a.search(2) == 2);

        CHECK(char_l.search((char*)"first") == 0);
        CHECK(char_l.search((char*)"second") == 1);
        CHECK(char_l.search((char*)"third") == 2);
    }
}

#endif //S20_PA01_SENTIMENTANALYSIS_TEST_H
#include <fstream>
#include <iostream>

#include "Index.h"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

//CATCH
int run_catch_test() {
    std::cout << "Catching..." << std::endl;
    return Catch::Session().run();
}

int main(int argc, const char* argv[]) {

    //CATCH
    run_catch_test();

    /**
     * RUN LOCAL
     */
    auto i = new Index();
    char *file = (char*)"input03.txt";
    i->readFile(file);
    i->print();
    i->writeToFile((char*)"output.txt");

    /**
     * FOR GITHUB
     */
//    auto i = new Index();
//    char *file = (char*)argv[1];
//    i->readFile(file);
//    i->writeToFile((char*)argv[2]);

    delete i;

    return 0;
}
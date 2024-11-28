// Project identifier: 1CAEF3A0FEDD0DEC26BA9808C69D4D22A9962768
#include <iostream>
#include <string>

#include "evaluate.hpp"


auto main() -> int {
    std::string expression = "12+3*";
    std::cout << evaluate(expression) << std::endl;
    std::string expression2 = "12+3*4/";
    std::cout << evaluate(expression2) << std::endl;
    //std::string expression3 = "12+3*4/5";
    //std::cout << evaluate(expression3) << std::endl;


    // wrong case: 
    return 0;
}

/*
 * NOTE: Since this file's name matches the glob pattern test*.cpp, the file is
 * a test file, NOT a source file! Nothing written here will be
 * submitted to the autograder.
 *
 * This also means there is no executable for this lab. Do not set EXECUTABLE
 * in your makefile to anything intended to be meaningful. Do not build with
 * `make release` or `make debug` or `make all` or just plain `make`; instead,
 * run `make help` and read the output that gives you, then use what you learn
 * from that to figure out how to build a test executable using this file.
 */
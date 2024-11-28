// Project Identifier: 2C4A3C53CD5AD45A7BEA3AE5356A3B1622C9D04B
// Testing file provided for EECS 281 Lab 7

#include "hashtable.h"
#include <string>
#include <iostream>

int main() {

    // VERY BASIC EXAMPLE (will likely not compile with default/empty hashtable.h file)
    HashTable<std::string, int> midterm;
    std::cout << midterm.size();
    std::cout << midterm.erase("sam") << " ";
    std::cout << midterm.insert("sam", 50) << " ";
    std::cout << midterm.size() << " " << " ";
    std::cout << midterm.insert("fee", 100) << " ";
    std::cout << midterm.insert("milo", 95) << " ";
    std::cout << midterm.insert("gabe", 88) << " \n";
    std::cout << midterm["sam"] << " ";
    std::cout << midterm["fee"] << " ";
    std::cout << midterm["milo"] << " ";
    std::cout << midterm["gabe"] << " \n";
    std::cout << midterm.erase("sam") << " ";
    std::cout << midterm["sam"] << "\n";
    // ADD MORE TESTS OF YOUR OWN



    std::cout << "\n\n\n";
    std::cout << "MY TESTS\n";
    HashTable<std::string, int> mt;
    std::cout << mt.size() << " ";
    std::cout << mt.erase("sam") << " ";
    std::cout << mt.insert("fan", 10) << " ";
    std::cout << mt.size() << " ";
    std::cout << mt["fan"] << " ";
    std::cout << mt.erase("fan") << " ";
    std::cout << mt.size() << " ";
    std::cout << mt["fan"] << " "; 

    mt.insert("sam", 50);
    mt.insert("fee", 100);
    mt.insert("milo", 95);
    mt.insert("gabe", 88);
    std::cout << mt.size() << " ";
    std::cout << mt["sam"] << " ";
    std::cout << mt["fee"] << " ";
    std::cout << mt["milo"] << " ";
    std::cout << mt["gabe"] << " ";
    mt["sam"] = 100;
    std::cout << mt["sam"] << " ";
    std::cout << mt.erase("sam") << " ";
    std::cout << mt["sam"] << " ";
    std::cout << mt.size() << " ";

    std::cout << "\n\n\n";
    std::cout << "Now we should insert more\n";
    mt["dm"] = 100;
    mt["dm"] = 200;
    mt["cm"] = 300;
    mt["cm"] = 400;
    mt["bm"] = 500;
    mt["bm"] = 600;
    mt["am"] = 700;
    mt["am"] = 800;
    mt["zm"] = 900;
    mt["zm"] = 1000;
    mt["ym"] = 1100;
    mt["ym"] = 1200;
    mt["xm"] = 1300;
    mt["xm"] = 1400;
    std::cout << mt.size() << " ";
    std::cout << mt["dm"] << " ";
    std::cout << mt["cm"] << " ";
    std::cout  << mt["bm"] << " ";
    std::cout  << mt["am"] << " ";
    std::cout  << mt["zm"] << " ";
    std::cout  << mt["ym"] << " ";
    std::cout  << mt["xm"] << " ";


    return 0;
}

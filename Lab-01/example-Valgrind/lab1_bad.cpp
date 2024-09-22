// Lab 01, testing with valgrind

// This program uses a Mersenne Twister to generate pseudo-random numbers.
// The fixed seed means it will generate the same sequence every time, on
// any computer system which properly implements the mt19937 algorithm.

// The random numbers are used as indices into a block of memory (of size
// 100), but the random numbers will be in the range [0, 110)!  If it can
// successfully initialize 10 elements of the array, it will then generate
// more random numbers and display the values at those indices.  If any of
// this second batch of random indices didn't occur in the first 10, the
// program would be trying to output an uninitialized value.

// Eventually something will go wrong.  Your task is to use valgrind to
// determine which problem occurs, and which line of code causes the first
// problem to be reported.

// Make sure you don't modify this file!  Adding or removing lines of
// code could cause you to report the wrong line number for your answers.
// The first initialization of an element of data should occur on line 60,
// and the first output of a value from the array should occur on line 72.

// To run this test, type the following commands:
//   make valgrind
//   valgrind ./lab1_bad_valgrind |& more

// You've probably never seen "|& more" before.  This means "when you run
// the specified program, send (pipe, vertical bar) the normal and error
// output (the ampersand) to the program more".  More is a "paginator"
// that will stop after every page.  This means you don't have to scroll
// back to find the first error, it will display one page and stop, waiting
// for you to decide when to display "more" of the output.  Press the space
// bar to go onto the next page, or "q" (with no quote marks) to quit.

// You can also use this if building your program is producing a lot of
// errors and you're having trouble scrolling back.  You can type:
//   make |& more
// If there's no errors, you probably won't have to hit the spacebar or q,
// since there should be less than one page of output.  You can also use
// more with a filename, such as the command:
//   more lab1_bad.cpp


#include <iostream>
#include <vector>
#include <random>
using namespace std;


constexpr size_t SIZE = 100;
constexpr size_t MOD = 110;


int main() {
    mt19937 mt(72521278);
    int *data = new int[SIZE];
    int count = 0;

    // Initialize some of the elements, possibly segfaulting
    data[mt() % MOD] = count++;
    data[mt() % MOD] = count++;
    data[mt() % MOD] = count++;
    data[mt() % MOD] = count++;
    data[mt() % MOD] = count++;
    data[mt() % MOD] = count++;
    data[mt() % MOD] = count++;
    data[mt() % MOD] = count++;
    data[mt() % MOD] = count++;
    data[mt() % MOD] = count++;

    // Output some of the elements, possibly getting an uninitialized value
    cout << data[mt() % MOD] << endl;
    cout << data[mt() % MOD] << endl;
    cout << data[mt() % MOD] << endl;
    cout << data[mt() % MOD] << endl;
    cout << data[mt() % MOD] << endl;
    cout << data[mt() % MOD] << endl;
    cout << data[mt() % MOD] << endl;
    cout << data[mt() % MOD] << endl;
    cout << data[mt() % MOD] << endl;
    cout << data[mt() % MOD] << endl;

    delete [] data;
    return 0;
} // main()

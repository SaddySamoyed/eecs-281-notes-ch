#include <iostream>
using namespace std;

template <typename TYPE>
void swap(TYPE &a, TYPE &b) {
    TYPE temp = a;
    a = b;
    b = temp;
}
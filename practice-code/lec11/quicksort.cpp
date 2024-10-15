#include <iostream>
using namespace std;



size_t partition(int a[], size_t left, size_t right) {
    size_t pivot = left + (right - left) / 2; // meddle point as 
}



void quicksort1(int a[], size_t left, size_t right) {
    if (left >= right) {
        return;
    }
    size_t pivot_index = partition(a, left, right);
    quicksort1(a, left, pivot_index);  //not tail
    quicksort1(a, pivot_index + 1, right); //tail recursion
}


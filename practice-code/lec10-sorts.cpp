#include <iostream>
using namespace std;


typedef int Item;


template <typename TYPE>
void swap(TYPE &a, TYPE &b) {
    TYPE temp = a;
    a = b;
    b = temp;
}


void bubble_sort(Item a[], size_t left, size_t right) {
    for (size_t i = left; i < right - 1; i++) {
        for (size_t j = right - 1; j > i; j--) {
            if (a[j] < a[j-1]) {
                std::swap(a[j], a[j-1]);
            }
        }
    }
}

void adaptive_bubble_sort(Item a[], size_t left, size_t right) {
    for (size_t i = left; i < right - 1; i++) {
        bool swapped = false;
        for (size_t j = right - 1; j > i; j--) {
            if (a[j] < a[j-1]) {
                std::swap(a[j], a[j-1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void selection_sort(Item a[], size_t left, size_t right) {
    for (size_t i = left; i < right - 1; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < right; j++) {
            if (a[j] < a[min_index]) {
                min_index = j;
            }
        }
        std::swap(a[i], a[min_index]);
    }
}

void adaptive_selection_sort(Item a[], size_t left, size_t right) {
    for (size_t i = left; i < right - 1; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < right; j++) {
            if (a[j] < a[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(a[i], a[min_index]);
        }
    }
}

void insertion_sort(Item a[], size_t left, size_t right) {
    for (size_t i = left + 1; i < right; i++) {
        // a[left:i] is sorted
        for (size_t j = i; i > left; --j) {
            // we expand the sorted region to a[left:i+1], 
            // by ctnsly move a[i+1] to the right position on the left
            if (a[j] < a[j-1]) {
                std::swap(a[j], a[j-1]);
            }
        }
    }
}

void improved_insertion_sort(Item a[], size_t left, size_t right) {
    for (size_t i = right - 1; i > left; --i) { // first find the min item, move to left
        if (a[i] < a[i-1]) {
            std::swap(a[i], a[i-1]);
        }
    }

    for (size_t i = left + 2; i < right; i++) {
        // a[left:i-1] is sorted
        Item v = a[i]; 
        size_t j = i;
        // while v in the wrong position j, we let a[j]=a[j-1], 
        // ready to move v to a[j-1] (when j-1 is the right pos)
        while (v < a[j-1]) {
            a[j] = a[j-1];
            j--;
        }
        a[j] = v;
    }
}



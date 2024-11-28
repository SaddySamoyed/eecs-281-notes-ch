/* 
 * palindrome.cpp 
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 1 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convenience.
// No need to use them. 
// Remove any of them if you want.
#include <algorithm>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "palindrome.h"

using namespace std;

bool isPalindrome(Node* start, Node* end) {
  Node* last_end = end;
  while (start != end && start != last_end) {
    if (start->value != end->value) {
      return false;
    }
    last_end = end;
    start = start->next;
    end = end->prev;
  }  
  return true;
}

int main() {
  // Add your test cases here.

  /*
  Node a, b, c, d, e;
  a.value = 'a';
  b.value = 'b';
  c.value = 'c';
  d.value = 'b';
  e.value = 'a';
  a.prev = nullptr;
  a.next = &b;
  b.prev = &a;
  b.next = &c;
  c.prev = &b;
  c.next = &d;
  d.prev = &c;
  d.next = &e;
  e.prev = &d;
  e.next = nullptr;
  cout << isPalindrome(&a, &e) << endl;
  
  Node a, b, c, d, e;
  a.value = 'a';
  b.value = 'b';
  c.value = 'c';
  d.value = 'd';
  e.value = 'a';
  a.prev = nullptr;
  a.next = &b;
  b.prev = &a;
  b.next = &c;
  c.prev = &b;
  c.next = &d;
  d.prev = &c;
  d.next = &e;
  e.prev = &d;
  e.next = nullptr;
  cout << isPalindrome(&a, &e) << endl;
  
  Node a, b, c, d, e, f;
  a.value = 'a';
  b.value = 'b';
  c.value = 'c';
  d.value = 'c';
  e.value = 'd';
  f.value = 'a';
  a.prev = nullptr;
  a.next = &b;
  b.prev = &a;
  b.next = &c;
  c.prev = &b;
  c.next = &d;
  d.prev = &c;
  d.next = &e;
  e.prev = &d;
  e.next = &f;
  f.prev = &e;
  f.next = nullptr;
  cout << isPalindrome(&a, &f) << endl;
  */

  Node a, b;
  a.value = 'a';
  b.value = 'a';
  a.prev = nullptr;
  a.next = &b;
  b.prev = &a;
  b.next = nullptr;
  cout << isPalindrome(&a, &b) << endl;

  Node c;
  c.value = 'c';
  c.prev = nullptr;
  c.next = nullptr;
  cout << isPalindrome(&c, &c) << endl;
  
  return 0;
}
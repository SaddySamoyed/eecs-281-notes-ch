/*
 * anagram.cpp
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 3 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convenience.
// No need to use them.
// Remove any of them if you want.
#include <algorithm>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
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

#include "anagram.h"

using namespace std;

bool isAnagram(const string &s1, const string &s2) {
    if (s1.length() != s2.length()) {
        return false;
    }

    unordered_map<char, int> charCount;
    for (char c : s1) {
        charCount[c]++;
    }

    for (char c : s2) {
        if (charCount.find(c) == charCount.end() || charCount[c] == 0) {
            return false;
        }
        charCount[c]--;
    }

    return true;
}

int main () {
    string s1 = "listen";
    string s2 = "silent";
    cout << isAnagram(s1, s2) << endl;

    string s3 = "hello";
    string s4 = "world";
    cout << isAnagram(s3, s4) << endl;
    return 0;
}
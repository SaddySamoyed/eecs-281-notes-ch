/*
 * replace_words.cpp
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 7 Written.
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

#include "replace_words.h"

using namespace std;

#include <vector>
#include <string>
#include <unordered_map>
#include <cassert>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    string findShortestPrefix(const string& word) {
        TrieNode* node = root;
        string prefix;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                break;
            }
            prefix += c;
            node = node->children[c];
            if (node->isEndOfWord) {
                return prefix;
            }
        }
        return word;
    }
};

vector<string> replace_words(const vector<string>& prefixes, const vector<string>& sentence) {
    Trie trie;
    for (const string& prefix : prefixes) {
        trie.insert(prefix);
    }

    vector<string> result;
    for (const string& word : sentence) {
        result.push_back(trie.findShortestPrefix(word));
    }

    return result;
}

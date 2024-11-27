/* 
 * two_pair_sums.cpp 
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 6 Written.
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


using namespace std;

void two_pair_sums(const vector<int>& nums, ostream& os) {
    unordered_map<int, pair<int, int>> sum_pairs;
    int n = nums.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = nums[i] + nums[j];

            // Check if we already have a pair with this sum
            if (sum_pairs.find(sum) != sum_pairs.end()) {
                pair<int, int> prev_pair = sum_pairs[sum];
                
                // Ensure all elements are distinct
                if (prev_pair.first != i && prev_pair.second != i && prev_pair.first != j && prev_pair.second != j) {
                    os << "(" << nums[prev_pair.first] << ", " << nums[prev_pair.second] << ") and ("
                    << nums[i] << ", " << nums[j] << ")\n";
                }
            } else {
                // Store the current pair
                sum_pairs[sum] = {i, j};
            }
        }
    }
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    two_pair_sums(nums, cout);
    return 0;
}
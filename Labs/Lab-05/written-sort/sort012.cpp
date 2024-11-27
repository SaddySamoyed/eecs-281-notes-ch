/* 
 * sort012.cpp 
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 5 Written.
 * THIS FILE FOR PRACTICE ONLY.
 * SUBMIT YOUR SOLUTION DIRECTLY TO INSTRUCTOR.
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

// a linear time, const space method to sort an array of 0s, 1s, and 2s
void sort012(vector<int>& nums) {
    int low = 0, scan = 0;
    int high = nums.size() - 1;

    while (scan <= high) {
        if (nums[scan] == 0) {
            std::swap(nums[low], nums[scan]);
            low++;
            scan++;
        } else if (nums[scan] == 2) {
            std::swap(nums[high], nums[scan]);
            high--;
        } else {
            scan++;
        }
    }
}

int main() {
  vector<int> nums = {0, 1, 2, 0, 1, 2, 0, 1, 2};
  sort012(nums);
  for (size_t i = 0; i < nums.size(); i++) {
    cout << nums[i] << " ";
  }
  cout << endl;
  vector<int> nums2 = {2,1,0,0,2,1,2,2};
  sort012(nums2);
  for (size_t i = 0; i < nums2.size(); i++) {
    cout << nums2[i] << " ";
  }
  cout << endl;

  vector<int> nums3 = {0,0,1,2,0,1,2};
  sort012(nums3);
  for (size_t i = 0; i < nums3.size(); i++) {
    cout << nums3[i] << " ";
  }
  return 0;
}
/* 
 * knapsack.cpp 
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 10 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convenience.
// No need to use them. 
// Remove any of them if you want.
#include <algorithm>
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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "knapsack.h"

using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to solve the Knapsack problem
int knapsack(int capacity, const vector<int>& value, const vector<int>& weight) {
    int itemNum = weight.size();
    vector<vector<int>> dp(itemNum + 1, vector<int>(capacity + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= itemNum; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weight[i - 1] <= w) {
                // Include the item or skip it
                dp[i][w] = max(dp[i - 1][w], value[i - 1] + dp[i - 1][w - weight[i - 1]]);
            } else {
                // Skip the item
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[itemNum][capacity];
}

int main() {
    int capacity;
    int n;

    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> weights(n);
    vector<int> values(n);

    cout << "Enter the weights of the items:\n";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    cout << "Enter the values of the items:\n";
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    int max_value = knapsack(capacity, weights, values);
    cout << "The maximum value that can be obtained is: " << max_value << endl;

    return 0;
}

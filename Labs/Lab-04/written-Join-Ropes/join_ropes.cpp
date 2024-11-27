#include <vector>
#include <queue>
#include <iostream>

int join_ropes(std::vector<int>& rope_lengths) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap(rope_lengths.begin(), rope_lengths.end());
    int total_cost = 0;
    
    while (min_heap.size() > 1) {
        int first = min_heap.top();
        min_heap.pop();
        int second = min_heap.top();
        min_heap.pop();

        int cost = first + second;
        total_cost += cost;
        min_heap.push(cost);
    }

    return total_cost;
}

int main() {
    std::vector<int> ropes = {10, 5, 8, 11};  // Example 1
    std::cout << "Minimum cost to connect ropes: " << join_ropes(ropes) << std::endl;
    
    ropes = {10, 5, 8, 14};  // Example 2
    std::cout << "Minimum cost to connect ropes: " << join_ropes(ropes) << std::endl;

    return 0;
}

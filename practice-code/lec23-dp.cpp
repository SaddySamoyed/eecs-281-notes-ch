#include<iostream> 
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;

static const size_t MAX_FIB = 100;



uint64_t naiveFibo(uint32_t i) {
    if (i == 1 || i == 0) return i;
    return naiveFibo(i-1) + naiveFibo(i-2);
}


uint64_t topDownFibo(uint32_t n) {
    static uint64_t memo[MAX_FIB + 1] = {0, 1}; //initial value
    // if n is too large, not in range of service
    if (n > MAX_FIB) return 0;
    // if already computed, return the value
    if (memo[n] > 0 || n==0) return memo[n];

    memo[n] = topDownFibo(n-1) + topDownFibo(n-2);
    return memo[n];
}


uint64_t bottomUpFibo(uint32_t n) {
    static uint64_t memo[MAX_FIB + 1] = {0, 1}; //initial value
    for (uint32_t i = 2; i <= n; i++) {
        memo[i] = memo[i-1] + memo[i-2];
    }
    return memo[n];
}


uint64_t binomialCoeffRecursion(uint32_t n, uint32_t k) {
    if (k == 0 || k == n) return 1;
    return binomialCoeffRecursion(n-1, k-1) + binomialCoeffRecursion(n-1, k);
}

uint64_t binomialCoeffHelper(uint32_t n, uint32_t k, vector<vector<uint64_t>>& memo) {
    if (k == 0 || k == n) {
        memo[k][n] = 1;
        return 1;
    }
    if (memo[k][n] > 0) return memo[k][n];
    memo[k][n] = binomialCoeffHelper(n-1, k-1, memo) + binomialCoeffHelper(n-1, k, memo);
    return memo[k][n];
}

uint64_t binomialCoeffTopDown(uint32_t n, uint32_t k) {
    vector<vector<uint64_t>> memo(k+1, vector<uint64_t>(n+1, 0));
    return binomialCoeffHelper(n, k, memo);
}

uint64_t binomialCoeffBottomUp(uint32_t n, uint32_t k) {
    vector<vector<uint64_t>> memo(k+1, vector<uint64_t>(n+1));
    for (size_t i = 0; i <= k; i++) {
        for (size_t j = i; j <= n; j++) {
            if (i==j || i==0) memo[i][j] = 1;
            else memo[i][j] = memo[i-1][j-1] + memo[i][j-1];
        }
    }
    return memo[k][n];
}



// Possible moves for a knight
vector<pair<int, int>> knightMoves = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};

int knightMoveDP(int plateWidth, int totalMoves, int startX, int startY, int destX, int destY) {
    // Initialize a 3D DP table with all zeros
    vector<vector<vector<int>>> dp(totalMoves + 1, vector<vector<int>>(plateWidth, vector<int>(plateWidth, 0)));
    
    // Base case: starting position
    dp[0][startX][startY] = 1;

    // Fill DP table
    for (int k = 1; k <= totalMoves; ++k) {
        for (int x = 0; x < plateWidth; ++x) {
            for (int y = 0; y < plateWidth; ++y) {
                if (dp[k - 1][x][y] > 0) { // If there are paths to this cell
                    for (auto move : knightMoves) {
                        int nx = x + move.first;
                        int ny = y + move.second;
                        if (nx >= 0 && nx < plateWidth && ny >= 0 && ny < plateWidth) { // Valid move
                            dp[k][nx][ny] += dp[k - 1][x][y];
                        }
                    }
                }
            }
        }
    }

    // Print the entire chessboard for the K-th step
    cout << "Chessboard at step " << totalMoves << ":" << endl;
    for (int x = 0; x < plateWidth; ++x) {
        for (int y = 0; y < plateWidth; ++y) {
            cout << dp[totalMoves][x][y] << " ";
        }
        cout << endl;
    }

    // Return the number of paths to (tx, ty) after K moves
    return dp[totalMoves][destX][destY];
}




int main() {
    uint32_t n = 10;
    cout << "Naive Fibonacci: " << naiveFibo(n) << endl;
    cout << "Top Down Fibonacci: " << topDownFibo(n) << endl;
    cout << "Bottom Up Fibonacci: " << bottomUpFibo(n) << endl;

    uint32_t k = 5;
    cout << "Binomial Coefficient Recursion: " << binomialCoeffRecursion(n, k) << endl;
    cout << "Binomial Coefficient Top Down: " << binomialCoeffTopDown(n, k) << endl;
    cout << "Binomial Coefficient Bottom Up: " << binomialCoeffBottomUp(n, k) << endl;

    int plateWidth = 8;
    int totalMoves = 4;
    int startX = 0, startY = 0;
    int destX = 3, destY = 3;
    knightMoveDP(plateWidth, totalMoves, startX, startY, destX, destY);
    return 0;
}
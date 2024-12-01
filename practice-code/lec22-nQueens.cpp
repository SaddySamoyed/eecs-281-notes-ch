#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using std::vector;
using namespace std;


class NQueens {
private:
    uint32_t size;
    uint64_t solutions, tried;
    vector<uint32_t> positionInRow;
    vector<bool> column, leftDiagonal, rightDiagonal;

    static const bool AVAILABLE;

    void putQueen(uint32_t row, bool display = true);
    bool promising(uint32_t row, uint32_t col);
    void displayBoard();

public:
    NQueens(uint32_t n);
    void solve(bool display = true);
    uint64_t getSolutions() const { return solutions; }
    uint64_t getTried() const { return tried; }
};  // NQueens{}


// Create the named constant
const bool NQueens::AVAILABLE = true;

// Construct the "available" 
NQueens::NQueens(uint32_t n) : size{n}, solutions{0}, tried{0},
    positionInRow(n, -1), column(n, AVAILABLE),
    leftDiagonal(2 * n - 1, AVAILABLE), rightDiagonal(2 * n - 1, AVAILABLE) {
}  // NQueens::NQueens()


// Solve this board (public member function)
// If display == true, display each board as a solution is found
void NQueens::solve(bool display) {
    putQueen(0, display);
}  // NQueens::solve()


// Is the proposed move promising?  It is promising if it
// would not violate any constraints
bool NQueens::promising(uint32_t row, uint32_t col) {
    return   column[col] == AVAILABLE
        && leftDiagonal[row + col] == AVAILABLE
        && rightDiagonal[row - col + (size - 1)] == AVAILABLE;
}  // NQueens::promising()


// Place a queen in row
// If display == true, display each board as a solution is found
void NQueens::putQueen(uint32_t row, bool display) {
    // Check for solution
    if (row == size) {
        ++solutions;
        if (display) {
            cout << "Solution found:\n";
            displayBoard();
        }  // if
        return;
    }  // if

    // Check every column within this row
    for (size_t col = 0; col < size; ++col) {
        // Check if proposed placement is promising
        if (promising(row, col)) {
            // Make the move, and a recursive call to next move
            positionInRow[row] = col;
            column[col] = !AVAILABLE;
            leftDiagonal[row + col] = !AVAILABLE;
            rightDiagonal[row - col + (size - 1)] = !AVAILABLE;
            putQueen(row + 1, display);

            // Undo this move and thus backtrack
            column[col] = AVAILABLE;
            leftDiagonal[row + col] = AVAILABLE;
            rightDiagonal[row - col + (size - 1)] = AVAILABLE;
        }  // if
        ++tried;
    }  // for
}  // NQueens::putQueen()


// Send the board to the screen
void NQueens::displayBoard() {
    string bar = "+";

    for (size_t col = 0; col < size; ++col)
        bar += "---+";

    for (size_t row = 0; row < size; ++row) {
        cout << "     " << bar << endl << "    ";

        for (size_t col = 0; col < size; ++col) {
            cout << " | ";
            if (positionInRow[row] == col)
                cout << "Q";
            else
                cout << " ";
        }  // for col
        cout << " |" << endl;
    }  // for row

    cout << "     " << bar << endl;
    cout << endl;
}  // NQueens::displayBoard()




int main() {
    uint32_t n;
    char display;
    double perms, savings;

    cout << "Enter number of queens: ";
    cin >> n;
    cout << "Display results? ";
    cin >> display;
    display = toupper(display);

    NQueens board(n);
    board.solve(display == 'Y');
    perms = pow(n, n);
    savings = (1 - (double)board.getTried() / perms) * 100;

    cout << "There were " << board.getSolutions() << " solutions\n";
    cout << board.getTried() << " branches were explored out of ";
    cout << perms << " possible permutations,\n";
    cout << "A savings of " << savings << "%\n";

    return 0;
}  // main()

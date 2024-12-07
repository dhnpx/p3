#include "grids.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>
using std::cout;
using std::string;
using std::vector;

bool is_valid_path(const vector<vector<char>> &grid,
                   const vector<char> &candidate, int rows, int cols);
long long soccer_exhaustive(vector<vector<char>> &grid);
int soccer_dynamic(vector<vector<char>> &grid);

int main() {
  // Given Sample

  for (auto grid : grids) {
    auto time_start = chrono::high_resolution_clock::now();
    long long sol_nums = soccer_exhaustive(grid);
    auto time_end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration_ms_double = time_end - time_start;
    cout << grid.size() << " x " << grid[0].size()
         << "\t Number of solutions: " << sol_nums
         << "\tDuration: " << duration_ms_double.count() << "ms" << endl;
  }
}

bool is_valid_path(const vector<vector<char>> &grid,
                   const vector<char> &candidate, int rows, int cols) {
  int col = 0, row = 0;

  for (char nextMove : candidate) {
    if (nextMove == '>')
      col++; // right

    else
      row++; // down

    // checking if an opponent is present at the current move or out of bounds
    if (col >= cols || row >= rows || grid[row][col] == 'X')
      return false;
  }

  // Reached goal post
  if (col == cols - 1 && row == rows - 1)
    return true;

  return false;
}
// 1. Exhaustive Search.
long long soccer_exhaustive(vector<vector<char>> &grid) {
  int rows = grid.size();
  int cols = grid[0].size();
  int n = rows + cols - 2; // -1 each for row and col
  long long paths = 0;
  //                        push bits left n many times
  for (__int128 bits = 0; bits < (1 << n); bits++) {
    vector<char> c;
    for (int i = 0; i < n; i++) {
      // extract the bit i many times
      int bit = (bits >> i) & 1;
      bit = bit ? '>' : 'v'; // 1 means right, 0 means down
      c.push_back(bit);
    }
    if (is_valid_path(grid, c, rows, cols)) {
      paths++;
    }
  }
  return paths;
}

int soccer_dynamic(vector<vector<char>> &grid) {
  int rows = grid.size();
  int cols = grid[0].size();
  // Corner case: Initial cell is impassible.
  if (grid[0][0] == 'X')
    return 0;

  // New r * c matrix initialized to zeroes.
  vector<vector<int>> grid2(rows, vector<int>(cols, 0));

  // Base case: A[0][0] == '.'
  grid2[0][0] = 1;

  // General Cases
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == 'X')
        continue;
    }
  }
  return grid2[rows - 1][cols - 1];
}

#include "grids.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

__int128 soccer_dyn_prog(vector<vector<char>> field) {
  if (field[0][0] == 'X') {
    return 0;
  }
  int rows = field.size();
  int cols = field[0].size();

  vector<vector<__int128>> A(rows, vector<__int128>(cols, 0));

  // base case
  A[0][0] = 1;

  // general cases
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (field[i][j] == 'X') {
        continue;
      }
      int above = 0, left = 0;
      if (i > 0 && field[i - 1][j] == '.') {
        above = A[i - 1][j];
      }
      if (j > 0 && field[i][j - 1] == '.') {
        left = A[i][j - 1];
      }
      A[i][j] += (above + left);
    }
  }
  return A[rows - 1][cols - 1];
}

int main() {
  for (auto grid : grids) {
    auto time_start = chrono::high_resolution_clock::now();
    __int128 sol_nums = soccer_dyn_prog(grid);
    auto time_end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration_ms_double = time_end - time_start;
    ostringstream str;
    str << sol_nums;
    string sol = str.str();
    cout << grid.size() << " x " << grid[0].size();
    cout << "\tNumber of solutions: %s" << sol
         << "\tDuration: " << duration_ms_double.count() << "ms" << endl;
  }
}

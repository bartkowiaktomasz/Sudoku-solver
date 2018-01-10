#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  load_board("board.dat", board);
  if (solve_board(board)) {
    cout << "The board has a solution:" << endl << endl;
    display_board(board);
    save_board("solution.dat", board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  return 0;
}

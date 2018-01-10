using namespace std;

/* Load board from file and write it to the 9x9 array */
void load_board(const char *filename, char board[9][9]);

/* Display board in the terminal window */
void display_board(const char board[9][9]);

/* Return true if board is solved, false otherwise */
bool is_complete(const char board[9][9]);

/* Return true if "digit" can be put at "position", false otherwise */
bool make_move(string position, char digit, char board[9][9]);

/* Return true if a "digit" is already used in a 3x3 sub-board,
false otherwise */
bool used_in_box(int row, int column, char digit, char board[9][9]);

/* Save solved board to a file */
bool save_board(string filename, char board[9][9]);

/* Solve board. Return true if board is solved, false otherwise */
bool solve_board(char board[9][9]);

/* Recursive function used to solve sudoku board. Return true if solution
is found, false otherwise */
bool solve_board_recursive(int row, int column, char *boardPtr, char board[9][9], const char initialBoard[9][9]);

/* If no digit is allowed at given field, backtrack function is called.
It moves to the previous field and increments its digit */
bool backtrack(int row, int column, char *boardPtr, char board[9][9], const char initialBoard[9][9]);

/* Move one cell forward on a board */
void cell_forward(int &row, int &column);

/* Move one cell backward on a board */
void cell_backward(int &row, int &column);

/* Convert row and column to a position string, i.e. "F5" */
string row_column_to_position(int row, int column);

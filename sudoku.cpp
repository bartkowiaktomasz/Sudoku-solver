#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <cctype>
#include <list>
#include "sudoku.h"

using namespace std;

void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++)
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

bool is_complete(const char board[9][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(!isdigit(board[i][j]))
                return false;
        }
    }
    return true;
}

bool make_move(string position, char digit, char board[9][9])
{
    int row = position[0] - 'A';
    int column = position[1] - '1';

    /* If position is incorrect, return false */
    if((row > 8 || row < 0) || (column > 8 || column < 0))
        return false;

    /* If position is occupited by a number, return false */
    if(isdigit(board[row][column]))
        return false;

    for(int i = 0; i < 9; i++)
    {
        /* If a digit appears in given row or column return false */
        if((board[row][i] == digit) ||
           (board[i][column] == digit))
            return false;

        /* If a digit appears in given 3x3 box return false */
        if(used_in_box(row, column, digit, board))
            return false;
    }

    board[row][column] = digit;
    return true;
}

bool used_in_box(int row, int column, char digit, char board[9][9])
{
    int initialRow = row - (row % 3);
    int initialColumn = column - (column % 3);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(!(i == row && j == column))
            {
                if(board[initialRow + i][initialColumn + j] == digit)
                    return true;
            }
        }
    }
    return false;
}

bool save_board(string filename, char board[9][9])
{
    ofstream outputFile;
    outputFile.open(filename);
    if(outputFile.fail())
        return false;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
            outputFile.put(board[i][j]);
        outputFile.put('\n');
    }
    outputFile.close();
    return true;
}

bool solve_board(char board[9][9])
{
    cout << endl;
    char initialBoard[9][9];
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
            initialBoard[i][j] = board[i][j];
    }
    char *boardPtr = board[0];
    if(solve_board_recursive(0, 0, boardPtr, board, initialBoard))
        return true;

    return false;
}

bool solve_board_recursive(int row, int column, char *boardPtr, char board[9][9], const char initialBoard[9][9])
{
    if(is_complete(board))
        return true;

    if(isdigit(initialBoard[row][column]))
    {
        cell_forward(row, column);
        return solve_board_recursive(row, column, boardPtr + 1, board, initialBoard);
    }
    else
    {
        string position;
        for(char digit = '1'; digit <= '9'; digit++)
        {
            position = row_column_to_position(row, column);
            if(make_move(position, digit, board))
            {
                cell_forward(row, column);
                return solve_board_recursive(row, column, boardPtr + 1, board, initialBoard);
            }
        }
        board[row][column] = '.';
        return backtrack(row, column, boardPtr - 1, board, initialBoard);
    }
}

bool backtrack(int row, int column, char *boardPtr, char board[9][9], const char initialBoard[9][9])
{
    cell_backward(row, column);

    if(row == -1)
        return false;

    if(isdigit(initialBoard[row][column]))
        return backtrack(row, column, boardPtr - 1, board, initialBoard);
    else
    {
        char temp;
        string position;
        if(board[row][column] < '9' && board[row][column] >= '0')
        {
            temp = board[row][column] + 1;
            board[row][column] = '.';
            position = row_column_to_position(row, column);
            if(make_move(position, temp, board))
            {
                cell_forward(row, column);
                return solve_board_recursive(row, column, boardPtr + 1, board, initialBoard);
            }
            else
            {
                board[row][column] = temp;
                cell_forward(row, column);
                return backtrack(row, column, boardPtr, board, initialBoard);
            }
        }
        else
        {
            board[row][column] = '.';
            return backtrack(row, column, boardPtr - 1, board, initialBoard);
        }
    }
}

void cell_forward(int &row, int &column)
{
    if(column < 8)
        column++;
    else
    {
        row++;
        column = 0;
    }
}

void cell_backward(int &row, int &column)
{
    if(column > 0)
        column--;
    else
    {
        row--;
        column = 8;
    }
}

string row_column_to_position(int row, int column)
{
    string position = "";
    position += (row + 'A');
    position += (column + '1');

    return position;
}

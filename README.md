# Sudoku-solver
Brute-force, backtracking (recursive) search sudoku solver in C++. The solver was part of an assignment on the C++ course at ICL (see specification.pdf).

To solve sudoku, just replace a board.dat file with initial numbers, where empty cells are represented as dots. Example .dat file:

```
...1.83..
24..5....
..8....61
..4..9..3
.6.....2.
3..8..1..
17....9..
....1..52
..27.4...
```

Example boards are: `easy.dat`, `medium.dat` and `mystery1.dat`, `mystery2.dat`, `mystery3.dat`.
Usage: compile with `make` and then type `./sudoku`.

### Stack smashing
In case of Segmentation fault, try increasing the stack by `ulimit -s unlimited`.

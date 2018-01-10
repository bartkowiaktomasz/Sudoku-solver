sudoku: main.o sudoku.o
	g++ -Wall -g main.o sudoku.o -o sudoku

main.o: main.cpp
	g++ -Wall -g -std=c++11 -c main.cpp -o main.o

sudoku.o: sudoku.cpp
	g++ -Wall -g -std=c++11 -c sudoku.cpp -o sudoku.o

clean:
	rm -f *.o sudoku

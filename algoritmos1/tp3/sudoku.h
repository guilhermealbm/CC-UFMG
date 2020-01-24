#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <map>

class Sudoku {
    private:
        int nCells, columnsSubGrid, rowsSubGrid;
        int *grid;
        std::vector<int> *adjacencyList;
        std::map<int, int> *cantBe;

        void connectRows();
        void connectColumns();
        void connectSubgrids();
        bool isSolved();
        int findBetterCell();
        void colorsAdjacentVertexes(int position, int value);
    public:
        Sudoku(int nCells, int rowsSubGrid, int columnsSubGrid);
        ~Sudoku();
        void addValue(int position, int value);
        void print();
        bool solve();
};

#endif
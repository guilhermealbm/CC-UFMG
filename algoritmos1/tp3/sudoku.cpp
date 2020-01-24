#include "sudoku.h"
#include <iostream>
#include <math.h>

Sudoku::Sudoku(int nCells, int rowsSubGrid, int columnsSubGrid) {
    this->nCells = nCells;
    this->columnsSubGrid = columnsSubGrid;
    this->rowsSubGrid = rowsSubGrid;

    this->adjacencyList = new std::vector<int>[nCells];
    this->cantBe = new std::map<int, int>[nCells];
    this->grid = new int[nCells];

    this->connectRows();
    this->connectColumns();
    this->connectSubgrids();
}

Sudoku::~Sudoku() {
    delete[] this->adjacencyList;
    delete[] this->cantBe;
    delete[] this->grid;
}

void Sudoku::addValue(int position, int value) {
    this->grid[position] = value;
    
    if(value != 0) {
        for(auto it = this->adjacencyList[position].begin(); it!=this->adjacencyList[position].end(); it++)
            this->cantBe[*it].insert(std::make_pair(value, -1));
    }
}

void Sudoku::connectRows() {
    int size = sqrt(nCells);
    for(int i = 0; i < this->nCells; i++){
        int row = i/size;

        for(int column = (i % size)+1; column < size; column++) {
            this->adjacencyList[i].push_back((row * size) + column);
            this->adjacencyList[(row * size) + column].push_back(i);
        }

    }
}

void Sudoku::connectColumns() {
    int size = sqrt(nCells);
    for(int i = 0; i < this->nCells; i++){
        int column = i%size;

        for(int row = (i / size)+1; row < size; row++) {
            this->adjacencyList[i].push_back((row * size) + column);
            this->adjacencyList[(row * size) + column].push_back(i);
        }

    }
}

void Sudoku::connectSubgrids() {
    int size = sqrt(nCells);
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            int root = (i * size) + j;
                //Iterate only on rows below the first one of each subgrid
                for(int row = i + 1; ((row < size) && (row % this->rowsSubGrid != 0)); row++) {
                    //Iterate only in columns of subgrid
                    for(int column = 0; column < this->columnsSubGrid; column++) {
                        //Calculates real value of subgrid column
                        int realColumn = column + ((j / this->columnsSubGrid) * this->columnsSubGrid);
                        int current = (row * size) + realColumn;
                        if(j != realColumn) { //Columns already connected
                            this->adjacencyList[root].push_back(current);
                            this->adjacencyList[current].push_back(root);
                        }
                    }
                }
        }
    }

}

bool Sudoku::isSolved(){
    for (int i = 0; i < this->nCells; i++) {
        if(this->grid[i] == 0)
            return false;
    }

    return true;
}

int Sudoku::findBetterCell(){
    unsigned int betterVertex = 0, betterValue = 0;

    for (int i = 0; i < this->nCells; i++) {
        if (this->cantBe[i].size() > betterValue && this->grid[i] == 0) {
            betterVertex = i;
            betterValue = this->cantBe[i].size();
        }
    }

    return betterVertex;
}

void Sudoku::colorsAdjacentVertexes(int position, int value){
    for(auto it = this->adjacencyList[position].begin(); it!=this->adjacencyList[position].end(); it++)
        this->cantBe[*it].insert(std::make_pair(value, -1));
}

void Sudoku::print() {
    int size = sqrt(nCells);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            std::cout << this->grid[i * size + j] << " ";

        std::cout << std::endl;
    }
}

bool Sudoku::solve() {
    //Found the best vertex to fill
    //Stop if sudoku is complete or fails because there's no more options to fill (and sudoku still incomplete)
    int canSolve = 1;

    while(canSolve == 1) {
        canSolve = 0;

        int currentVertex = this->findBetterCell();

        for (int i = 0; i < (sqrt(this->nCells)); i++) {
            int canColor = 1;

            if(this->cantBe[currentVertex].find(i+1) != this->cantBe[currentVertex].end())
                canColor = 0;
            
            if (canColor) {
                canSolve = 1;
                this->grid[currentVertex] = i+1;
                this->colorsAdjacentVertexes(currentVertex, i+1);
                break;
            }
        }

        if(this->isSolved())
            return true;
    }

    return false;
}
#include <iostream>
#include <fstream>

#include "sudoku.h"

void read_input_file(std::string file_name){
    std::ifstream readFile;
    readFile.open(file_name);
    
    if(readFile.is_open()){
        int size, columnsSubGrid, rowsSubGrid, value;
        readFile >> size >> columnsSubGrid >> rowsSubGrid;

        Sudoku sudoku = Sudoku(size*size, rowsSubGrid, columnsSubGrid);

        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                readFile >> value;
                sudoku.addValue(((i * size) + j), value);
            }
            
        }

        if(sudoku.solve())
            std::cout << "solução" << std::endl;
        else
            std::cout << "sem solução" << std::endl;
            
        sudoku.print();
    
    }

    readFile.close();
}

int main(int argc, char *argv[]){
    
    read_input_file(std::string(argv[1]));

    return 0;
}
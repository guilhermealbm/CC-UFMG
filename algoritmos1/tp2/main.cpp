#include <iostream>
#include <fstream>
#include "tripUtils.h"

void read_input_file (std::string file_name) {
    std::ifstream readFile;
    readFile.open(file_name);
    
    if(readFile.is_open()){
        int maxCost, islands;
        readFile >> maxCost >> islands;

        Island archipelago[islands];

        for (int i = 0; i < islands; i++){
            int costPerDay, score;
            double factor;
            readFile >> costPerDay >> score;
            factor = ((double)score/(double)costPerDay);
            archipelago[i] = {costPerDay, score, factor};
        }

        std::pair<int, int> greedyResult = TripUtils::runGreedy(archipelago, islands, maxCost);
        std::cout << greedyResult.first << " " << greedyResult.second << std::endl;
        std::pair<int, int> dynamicResult = TripUtils::runDynamic(archipelago, islands, maxCost);
        std::cout << dynamicResult.first << " " << dynamicResult.second << std::endl;
    }

    readFile.close();
}

int main(int argc, char *argv[]){
    
    read_input_file(std::string(argv[1]));

    return 0;
}
#ifndef TRIPUTILS_H
#define TRIPUTILS_H

#include <utility>

struct Island{
    int costPerDay;
    int score;
    double factor;
};

class TripUtils {
private:
    // Disallow creating an instance of this object
    TripUtils(){};    
public:
    static std::pair<int, int> runGreedy(Island archipelago[], int n, int maxCost);
    static std::pair<int, int> runDynamic(Island archipelago[], int n, int maxCost);
    static int max(int a, int b);
    static void merge(Island archipelago[], int left, int middle, int right);
    static void mergeSort(Island archipelago[], int left, int right);
};

#endif
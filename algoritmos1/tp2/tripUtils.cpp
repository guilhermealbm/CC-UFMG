#include "tripUtils.h"

std::pair<int, int> TripUtils::runGreedy(Island archipelago[], int n, int maxCost) {

    TripUtils::mergeSort(archipelago, 0, n-1);
    int totalDays = 0, totalScore = 0;
    //Descending sorted array
    for (int i = n-1; i >= 0; i--) {
        if(archipelago[i].costPerDay <= maxCost) {
            int nDays = maxCost/archipelago[i].costPerDay;
            totalDays += nDays;
            totalScore += nDays * archipelago[i].score;
            maxCost -= nDays * archipelago[i].costPerDay;
        }
    }

    return std::pair<int, int>(totalScore, totalDays);    

}

int TripUtils::max(int a, int b) { return (a > b)? a : b; } 

std::pair<int, int> TripUtils::runDynamic(Island archipelago[], int n, int maxCost) {
    int i, j, totalDays = 0, totalScore = 0; 
    int table[n+1][maxCost+1]; 
  
   // Build table bottom up
   for (i = 0; i <= n; i++) { 
       for (j = 0; j <= maxCost; j++) { 
           if (i==0 || j==0) 
               table[i][j] = 0; //Fills first line and first column
           else if (archipelago[i-1].costPerDay <= j) 
                 table[i][j] = TripUtils::max(archipelago[i-1].score + table[i-1][j-archipelago[i-1].costPerDay],  table[i-1][j]); 
           else
                 table[i][j] = table[i-1][j]; 
       }
   }
  
   totalScore = table[n][maxCost]; 

   // Backtracking for totalDays count
    for (i = n, j = maxCost; i > 0 && j > 0; i--) {
        if (table[i - 1][j] != table[i][j]) {
            totalDays++;
            j -= archipelago[i-1].costPerDay;
        }
    }

    return std::pair<int, int>(totalScore, totalDays);

}

void TripUtils::merge(Island archipelago[], int left, int middle, int right)  {
    int i, j;
    int n1 = middle - left + 1; 
    int n2 =  right - middle; 
  
    Island leftArray[n1], rightArray[n2]; 

    //Copy values
    for (i = 0; i < n1; i++) 
        leftArray[i] = archipelago[left + i]; 
    for (j = 0; j < n2; j++) 
        rightArray[j] = archipelago[middle + 1+ j]; 
  
    i = 0, j = 0;
    int k = left;

    //Merge the temp arrays
    while (i < n1 && j < n2) { 
        if (leftArray[i].factor <= rightArray[j].factor) { 
            archipelago[k] = leftArray[i]; 
            i++; 
        } else { 
            archipelago[k] = rightArray[j]; 
            j++; 
        } 
        k++; 
    } 

    //Copy remaining elements
    while (i < n1) { 
        archipelago[k] = leftArray[i]; 
        i++; 
        k++; 
    } 
    
    while (j < n2) { 
        archipelago[k] = rightArray[j]; 
        j++; 
        k++; 
    } 
} 

void TripUtils::mergeSort(Island archipelago[], int left, int right) { 
    if (left < right) { 
  
        mergeSort(archipelago, left, (left + right)/2); 
        mergeSort(archipelago, ((left + right)/2)+1, right); 
  
        merge(archipelago, left, (left + right)/2, right); 
    } 
} 
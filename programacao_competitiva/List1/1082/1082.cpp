#include <iostream>
#include <set>
#include <vector>
 
using namespace std;

void getComponents(int matrix[][26], int curr, int v, set<int> &visited, set<int> &currDfs) {
    visited.insert(curr);
    currDfs.insert(curr);
    for (size_t i = 0; i < v; i++) {
        const bool is_in = visited.find(i) != visited.end();
        if (matrix[curr][i] == 1 && !is_in) {
            getComponents(matrix, i, v, visited, currDfs);
        }
    }
}
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
     int tttt;cin >> tttt;
     for (int i = 0; i < tttt; i++) {
         int matrix[26][26] = {0};
         int v;cin >> v;
         int e;cin >> e;
         for (int j = 0; j < e; j++) {
             char v1;cin >> v1;
             char v2;cin >> v2;
             matrix[v1 - 97][v2 - 97] = 1;
             matrix[v2 - 97][v1 - 97] = 1;
         }

         set<int> visited;
         cout << "Case #" << i + 1 << ":" << endl;
         int components = 0;
         for (size_t j = 0; j < v; j++) {
             const bool is_in = visited.find(j) != visited.end();
             if (! is_in) {
                 components++;
                set<int> currDfs;
                getComponents(matrix, j, v, visited, currDfs);
                for (auto curr = currDfs.begin(); curr != currDfs.end(); curr++)
                    cout << char(97 + *curr) << ",";
                cout << endl;
             }
         }
         cout << components << " connected components" << endl << endl;
     }
}

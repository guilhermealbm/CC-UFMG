#include <iostream>
#include <algorithm>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    int n;
    while (cin >> n) {
        if (n == 0) return 0;

        int arrayX[1001] = { 0 };
        int arrayY[1001] = { 0 };
        long long matrix[1001][1001] = { 0 };
        for (int i = 0; i < n; i++) {
            int x, y; cin >> x; cin >> y;
            arrayX[i] = x;
            arrayY[i] = y;
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long long x = arrayX[i] - arrayX[j];
                long long y = arrayY[i] - arrayY[j];
                matrix[i][j] = x * x + y * y;
            }

            sort(matrix[i], matrix[i] + n);

            long long end = -1;
            int aux = 0;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != end) { 
                    ans += (aux * (aux - 1)) / 2;
                    aux = 0;
                }

                end = matrix[i][j];
                aux++;
            }
            
            ans += (aux * (aux - 1)) / 2;
            
        }
        
        cout << ans << endl;
        
    }
 
    return 0;
}
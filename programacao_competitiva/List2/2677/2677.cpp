#include <iostream>
 
using namespace std;
 
int main() {
 
    /**
     * Escrearraya a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    int n;

    while (cin >> n) {

        if (n == 0)
            break;

        int array[1000] = {0};
        int matrix[1001][1001] = {0};

        for (int i = 0; i < 2 * n; i++) {
            int num; cin >> num;
            array[i] = num;
        }

        int k;

        for (int i = 0; i < 2 * n; i++) {
            for (int j = 0; j + i < 2 * n; j++) {
                k = i + j;

                if (i % 2 == 0) {
                    matrix[j][k] = min(matrix[j + 1][k], matrix[j][k - 1]);
                } else {
                    int aux;
                    if (array[j] % 2 == 0)
                        aux = 1;
                    else
                        aux = 0;

                    int aux2;
                    if (array[k] % 2 == 0)
                        aux2 = 1;
                    else
                        aux2 = 0;

                    matrix[j][k] = max(matrix[j + 1][k] + aux, matrix[j][k - 1] + aux2);
                }
            }
        }

        cout << matrix[0][2 * n - 1] << endl;
        
    }
    
    return 0;
}
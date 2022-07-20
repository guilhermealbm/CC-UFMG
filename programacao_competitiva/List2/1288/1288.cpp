#include <iostream>
 
using namespace std;

typedef struct sack
{
    int weight, value;

    sack(int a, int b) :
       weight(a),
       value(b) 
    {}

    sack() :
       weight(0),
       value(0) 
    {}
} sack;
 
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    int tttt; cin >> tttt;
    while (tttt--) {
        int n; cin >> n;
        sack packages[50];
        for (size_t i = 0; i < n; i++) {
            int x, y; cin >> x; cin >> y;
            packages[i] = sack(y, x);
        }

        int k; cin >> k;
        int r; cin >> r;

        int matrix[51][101] = {0};

        for (size_t w = 0; w <= k; w++) {
            for (size_t i = 1; i <= n; i++) {
                if (packages[i - 1].weight > w) {
                    matrix[i][w] = matrix[i - 1][w];
                } else {
                    matrix[i][w] = max(matrix[i - 1][w], packages[i-1].value 
                    + matrix[i - 1][w - packages[i - 1].weight]);
                }
            }
        }

        if (matrix[n][k] >= r)
            cout << "Missao completada com sucesso" << endl;
        else
            cout << "Falha na missao" << endl;
        
    }
 
    return 0;
}
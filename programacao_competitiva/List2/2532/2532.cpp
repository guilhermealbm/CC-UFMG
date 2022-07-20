#include <iostream>
 
 #define INF 0x3f3f3f3f
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

    int n;
    while (cin >> n) {

        int p;
        cin >> p;
        sack spells[1000];
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int d, m;
            cin >> d; cin >> m;
            sum += d;
            spells[i] = sack(m, d);
        }

        int matrix[1001][2001] = {0};

        for (int w = 0; w <= p; w++) {
            for (int i = 1; i <= n; i++) {
                if (spells[i - 1].value >= w) {
                    int aux = INF;
                    if (matrix[i - 1][w] > 0) 
                        aux = matrix[i - 1][w];

                    matrix[i][w] = min(aux, spells[i - 1].weight);
                } else {
                    int aux = 0;
                    if (matrix[i - 1][w - spells[i - 1].value] > 0)
                        aux = spells[i-1].weight + matrix[i - 1][w - spells[i - 1].value];

                    int aux2 = INF;
                    if (matrix[i - 1][w] > 0)
                        aux2 = matrix[i - 1][w];

                    matrix[i][w] = min(aux, aux2);
                }
            }
        }

        if (matrix[n][p] > 0)
            cout << matrix[n][p] << endl;
        else
            cout << -1 << endl;

    }
 
    return 0;
}

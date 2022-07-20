#include <iostream>
#include <algorithm>
 
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

    int tttt;cin>>tttt;
    int maxCapacity = 50;
	while (tttt--) {
        sack packages[100];
        int pac;cin>>pac;
        for (size_t i = 0; i < pac; i++) {
            int qt;cin>>qt;
            int peso;cin>>peso;
            packages[i] = sack(peso, qt);
        }

        int matrix[101][51] = {0};
        for (size_t w = 0; w <= maxCapacity; w++) {
            for (size_t i = 1; i <= pac; i++) {
                if (packages[i - 1].weight > w) {
                    matrix[i][w] = matrix[i - 1][w];
                } else {
                    matrix[i][w] = max(matrix[i - 1][w], packages[i-1].value 
                    + matrix[i - 1][w - packages[i - 1].weight]);
                }
            }
        }
        
        cout << matrix[pac][maxCapacity] << " brinquedos"<< endl;

        int i = pac;
        int j = maxCapacity;
        int count = pac;
        while (i > 0 && j >= 0) {
            if (matrix[i][j] > matrix[i - 1][j]) {
                j -= packages[i - 1].weight;
                count--;
            }
            i--;
        }

        cout << "Peso: " << maxCapacity - j << " kg" << endl;
        cout << "sobra(m) " << count << " pacote(s)" << endl << endl;
        

    }
 
    return 0;
}

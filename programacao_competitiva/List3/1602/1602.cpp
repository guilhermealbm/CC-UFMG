#include <iostream>
#include <vector>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    int n;
    int max_ = 2000001;

    vector<int> primeNumbers(max_ + 1, 0);
    vector<int> finalVector(max_ + 1, 0);
    primeNumbers[0] = 0, finalVector[0] = 0;
    primeNumbers[1] = 0, finalVector[1] = 0;
    for (int i = 2; i <= max_; i++) {
        if (primeNumbers[i] == 0) {
            primeNumbers[i] = -1;
            for (int j = i + i; j <= max_; j += i) {
                int aux = 0;
                int size = j;
                while (size % i == 0) {
                    size /= i;
                    aux++;
                }

                aux++;
                if (primeNumbers[j] == 0)
                    primeNumbers[j] = aux;
                else
                    primeNumbers[j] *= aux;
            }
        }
    }

    for (int i = 2; i <= max_; i++) {
        finalVector[i] = finalVector[i - 1];
        if (primeNumbers[i] == 0 || primeNumbers[i] == -1 || (primeNumbers[i] != -1 && primeNumbers[primeNumbers[i]] == -1))
            finalVector[i] += 1;
    }
    

    // for (int i = 2357; i < 2358; i++) {
    //     cout << i << "   " << primeNumbers[i] << endl;
    //     cout << i << "   " << finalVector[i] << endl;
    // }
    

    while (cin >> n) {
        cout << finalVector[n] << endl;
    }
 
    return 0;
}
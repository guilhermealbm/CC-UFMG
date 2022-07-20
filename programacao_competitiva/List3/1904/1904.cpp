#include <iostream>
#include <vector>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    int a; int b; cin >> a; cin >> b;

    if (a == b) cout << "?" << endl;
    else {
        int k = abs(a - b);
        int max_ = max(a, b);
        vector<bool> primeNumbers(max_ + 1, true);
        primeNumbers[0] = false;
        primeNumbers[1] = false;
        for (int j = 4; j <= max_; j += 2) {
            primeNumbers[j] = false;
        }
        for (int i = 3; i * i <= max_; i += 2) {
            if (primeNumbers[i]) {
                for (int j = i * i; j <= max_; j += i) {
                    primeNumbers[j] = false;
                }
            }
        }

        int min_ = min(a, b);
        int primes = 0;
        for (int i = min_; i <= max_; i++) {
            if (primeNumbers[i]) {
                primes++;
            }
        }

        if (primes == 0) {
            cout << "Bob" << endl;
        } else if (int((primes + k - 1) & k) == k) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }
    }
 
    return 0;
}

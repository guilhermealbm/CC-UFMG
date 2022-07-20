#include <iostream>
#include <string>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    int n;
    while (cin >> n) {
        if (n == 0) cout << "Nada" << endl;
        else if (n == 1) cout << "Nada" << endl;
        else if (n == 2) cout << "Super" << endl;
        else {
            if (n % 2 == 0) cout << "Nada" << endl;
            else {
                bool isNothing = false;
                for (int i = 3; i * i <= n; i = i + 2) {
                    if (n % i == 0 && n != i) {
                        cout << "Nada" << endl;
                        isNothing = true;
                        break;
                    }
                }

                if (!isNothing) {
                    string num = to_string(n);
                    for (int i = 0; i < num.length(); i++) {
                        if (num[i] != '2' & num[i] != '3' &  num[i] != '5' &  num[i] != '7') {
                            cout << "Primo" << endl;
                            isNothing = true;
                            break;
                        }
                    }
                    if (!isNothing)
                        cout << "Super" << endl;
                }
            }
        }
    }
    return 0;
}
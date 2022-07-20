#include <iostream>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    int tttt; cin >> tttt;
    while (tttt--) {
        int n; cin >> n;
        bool end = false;
        int a = 0;
        int b = 0;
        while (n--) {
            int curr; cin >> curr;
            if (a + curr > b + 5) {
                if (b + curr > a + 5)
                    end = true;
                else
                    b += curr;
            } else {
                a += curr;
            }

            if (a > b + 5) {
                end = true;
            }
        }
        if (end)
            cout << "Ho Ho Ho!" << endl;
        else
            cout << "Feliz Natal!" << endl;
    }
 
    return 0;
}

#include <iostream>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
     
     double value;cin>>value;
     cout << "NOTAS:" << endl;
     
     value = value * 100;
     
     int n1 = value / 10000;
     value = value - n1 * 10000;
     
     cout << n1 << " nota(s) de R$ 100.00" << endl;
     
     n1 = value / 5000;
     value = value - n1 * 5000;
     cout << n1 << " nota(s) de R$ 50.00" << endl;
     
     n1 = value / 2000;
     value = value - n1 * 2000;
     cout << n1 << " nota(s) de R$ 20.00" << endl;
     
     n1 = value / 1000;
     value = value - n1 * 1000;
     cout << n1 << " nota(s) de R$ 10.00" << endl;
     
     n1 = value / 500;
     value = value - n1 * 500;
     cout << n1 << " nota(s) de R$ 5.00" << endl;
     
     n1 = value / 200;
     value = value - n1 * 200;
     cout << n1 << " nota(s) de R$ 2.00" << endl;
     
     cout << "MOEDAS:" << endl;
     
     n1 = value / 100;
     value = value - n1 * 100;
     cout << n1 << " moeda(s) de R$ 1.00" << endl;
     
     n1 = value / 50;
     value = value - n1 * 50;
     cout << n1 << " moeda(s) de R$ 0.50" << endl;
     
     n1 = value / 25;
     value = value - n1 * 25;
     cout << n1 << " moeda(s) de R$ 0.25" << endl;
     
     n1 = value / 10;
     value = value - n1 * 10;
     cout << n1 << " moeda(s) de R$ 0.10" << endl;
     
     n1 = value / 5;
     value = value - n1 * 5;
     cout << n1 << " moeda(s) de R$ 0.05" << endl;
     
     cout << value << " moeda(s) de R$ 0.01" << endl;
 
    return 0;
}
#include <iostream>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
     
     string value;cin>>value;
     int size = value.length();
     int n = 0;
     
     for (int i = 0; i < size; i++)
        n = n + ((int) value[i]);
     
     cout << n % 3 << endl;
 
    return 0;
}
#include <iostream>
#include <set>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
     
     set<string> jews;
     string jew;
     while (cin>>jew) {
         jews.insert(jew);
     }
     
     cout << jews.size() << endl;
 
    return 0;
}
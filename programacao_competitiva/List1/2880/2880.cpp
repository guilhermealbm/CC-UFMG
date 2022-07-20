#include <iostream>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
     
    string message;cin>>message;
    string crib;cin>>crib;
    
    int messageLen = message.length();
    int cribLen = crib.length();
    int ans = 0;
    for (int i = 0; i <= messageLen - cribLen; i++) {
        bool isPossible = true;
        for (int j = 0; j < cribLen; j++) {
            if (message[i + j] == crib[j]) {
                isPossible = false;
                break;
            }
        }
        if (isPossible)
            ans++;
    }
    
    cout << ans << endl;
 
    return 0;
}
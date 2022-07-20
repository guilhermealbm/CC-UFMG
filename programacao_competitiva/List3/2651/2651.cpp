#include <iostream>
#include <algorithm>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    string s; cin >> s;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    if (s.find("zelda") != std::string::npos) {
        cout << "Link Bolado" << endl;
    } else {
        cout << "Link Tranquilo" << endl;
    }
 
    return 0;
}

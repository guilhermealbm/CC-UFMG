#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define INF 0x3f3f3f3f
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
    int tttt;cin>>tttt;
    while(tttt--) {
        int n; cin >> n;
        int athletes[51] = {0};
        for (size_t i = 0; i < n; i++) {
            int curr;cin>>curr;
            athletes[i] = curr;
        }
 
        sort(begin(athletes), end(athletes));
 
        int start = 51 - n;
        int minDiff = INF;
        for (size_t i = start; i < 50; i++) {
            if (athletes[i + 1] - athletes[i] < minDiff) {
                minDiff = athletes[i + 1] - athletes[i];
            }
        }
        
        cout << minDiff << endl;
 
    }
 
    return 0;
}
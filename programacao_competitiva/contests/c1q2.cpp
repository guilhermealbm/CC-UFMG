#include <iostream>
#include <vector>
 
using namespace std;
 
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
 
int main() { _
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
    int tttt;cin>>tttt;
    while(tttt--) {
        int n; cin >> n;
        vector<long long> array;
        for (int i = 0; i < n; i++) {
            long long curr;cin>>curr;
            array.push_back(curr);
        }
 
        for (int i = n - 2; i >= 0; i--) {
            if (array[i] + i < n)
                array[i] += array[i + array[i]];
        }
 
        long long currMax = -1;
        for (int i = 0; i < n; i++) {
            if (array[i] > currMax)
                currMax = array[i];
        }
        cout << currMax << endl;
    }
    return 0;
}
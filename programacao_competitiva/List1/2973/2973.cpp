#include <iostream>
#include <cmath>
#include <vector>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    int n;cin>>n;
    int c;cin>>c;
    int t;cin>>t;

    vector<int> ll;

    long long total = 0;

    for (size_t i = 0; i < n; i++) {
        int qte;cin>>qte;
        total += qte;
        ll.push_back(qte);
    }

    long long firstP = 0;
    long long lastP = total;
    long long half = (lastP + firstP) / 2;

    while (firstP + 1 < lastP) {
        // cout << firstP << "  " << lastP << endl;
        half = (lastP + firstP) / 2.0;
        int i = 0;
        int j = 0;
        long long currC = 0;
        long long currT = 0;
        while (i < c && j < n) {
            if (currC + ll.at(j) <= half) {
                currC += ll.at(j);
                currT += ll.at(j);
                j++;
            } else {
                currC = 0;
                i++;
            }
        }
        
        if (total > currT) {
            firstP = half;
        } else {
            lastP = half;
        }

    }

    cout << int(ceil(((lastP + firstP) / 2.0) / float(t))) << endl;
 
    return 0;
}

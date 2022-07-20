#include <math.h>
#include <iostream>
#include <set>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
    long long n;cin>>n;
    long long curr = (long long) n;
    set<long long> divisors;
    while (curr % 2 == 0) {
        divisors.insert(2);
        curr = curr/2;
    }
 
    for (long long i = 3; i <= sqrt(n); i = i + 2) {
        while (curr % i == 0) {
            divisors.insert(i);
            curr = curr/i;
        }
    }

    if (curr != 0 && curr != 1) {
        divisors.insert(curr);
    }

    long long total = 0;
    total = pow(2,  divisors.size()) - (divisors.size() + 1);

    cout << total << endl;
 
    return 0;
}
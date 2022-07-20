#include <iostream>
#include <vector>
 
using namespace std;
typedef pair<int, int> ii;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    vector<int> cols;

    int tttt;cin >> tttt;
    while (tttt--) {
        int curr; cin >> curr;
        cols.push_back(curr);
    }

    vector<ii> leftRight;
    leftRight.push_back({1, 1});
    for (size_t i = 1; i < cols.size(); i++) {
        if (cols[i] < leftRight[i - 1].first + 1) {
            leftRight.push_back({cols[i], 1});
        } else {
            leftRight.push_back({leftRight[i - 1].first + 1, 1});
        }
    }

    for (int i = cols.size() - 2; i >= 0; i--) {
        if (cols[i] < leftRight[i + 1].second + 1) {
            leftRight[i].second = cols[i];
        } else {
            leftRight[i].second = leftRight[i + 1].second + 1;
        }
    }

    int max = 0;
    for (size_t i = 0; i < leftRight.size(); i++) {
        int min = leftRight[i].first > leftRight[i].second ? leftRight[i].second : leftRight[i].first;
        if (min > max)
            max = min;
    }

    cout << max << endl;
 
    return 0;
}

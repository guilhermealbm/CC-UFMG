#include <iostream>
#include <vector>
 
using namespace std;

int checkEquals(const int a[], int n) {   
    while(--n>0 && a[n]==0);
    return n!=0;
}
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
     int lamps[1001] = {0};
     int lampsN;cin>>lampsN;
     int inter;cin>>inter;
     int on;cin>>on;
     while(on--) {
         int curr;cin>>curr;
         lamps[curr] = 1;
     }

     int lampN;
     bool canDo = false;
     int i = 0;
     vector<vector<int> > input;
     while (cin>>lampN) {
         vector<int> input_;
        while(lampN--) {
             int curr;cin>>curr;
             input_.push_back(curr);
         }
         input.push_back(input_);
     }

    int total = 0;
     for (int i = 0; i < input.size(); i++) {
         int allEquals = checkEquals(lamps, lampsN + 1);
         if (allEquals == 0) {
             if (lamps[0] == 0) {
                 canDo = true;
                 break;
             } else {
                 canDo = true;
                 break;
             }
         }
         for (int j = 0; j < input[i].size(); j++) {
             lamps[input[i][j]] = !lamps[input[i][j]];
         }
         total++;
     }

     for (int i = 0; i < input.size(); i++) {
         int allEquals = checkEquals(lamps, lampsN + 1);
         if (allEquals == 0) {
             if (lamps[0] == 0) {
                 canDo = true;
                 break;
             } else {
                 canDo = true;
                 break;
             }
         }
         for (int j = 0; j < input[i].size(); j++) {
             lamps[input[i][j]] = !lamps[input[i][j]];
         }
         total++;
     }
     
     if (canDo)
        cout << total << endl;
    else
        cout << -1 << endl;
 
    return 0;
}
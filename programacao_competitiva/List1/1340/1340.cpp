#include <iostream>
#include <queue>
#include <stack>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
     int tttt;
     while( cin >> tttt ){
         bool boolpq = true;
         bool boolq = true;
         bool bools = true;
         
         priority_queue<int> pq;
         queue<int> q;
         stack<int> s;
         for(int i = 0; i < tttt; i++) {
             int elem1;cin>>elem1;
             int elem2;cin>>elem2;
             
             if (elem1 == 1) {
                 // push
                 pq.push(elem2);
                 q.push(elem2);
                 s.push(elem2);
             } else {
                 // remove
                 int resultpq = 0;
                 int resultq = 0;
                 int results = 0;
                 
                 if (pq.size() <= 0) {
                     boolpq = false;
                 } else {
                     resultpq = pq.top();
                     pq.pop();
                 }
                 
                 if (q.size() <= 0) {
                    boolq = false;
                 } else {
                    resultq = q.front();
                    q.pop();
                 }
                 
                 if (s.size() <= 0) {
                     bools = false;
                 } else {
                     results = s.top();
                     s.pop();
                 }
                 
                 if (elem2 != resultpq) {
                     boolpq = false;
                 }
                 
                 if (elem2 != resultq) {
                     boolq = false;
                 }
                 
                 if (elem2 != results) {
                     bools = false;
                 }
             }
         }
         
         if (boolpq && !boolq && !bools) {
             cout << "priority queue" << endl;
         } else if (!boolpq && boolq && !bools) {
             cout << "queue" << endl;
         } else if (!boolpq && !boolq && bools) {
             cout << "stack" << endl;
         } else if (!boolpq && !boolq && !bools) {
             cout << "impossible" << endl;
         } else {
             cout << "not sure" << endl;
         }
     }
 
    return 0;
}
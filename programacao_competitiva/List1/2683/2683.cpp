#include <iostream>
#include <vector>
#include <queue>


#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3fLL
 
using namespace std;
typedef pair<int, int> ii;

int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
     int tttt;cin>>tttt;
     vector<ii> adj[1000];
     priority_queue<ii> pq;
     bool visited[1000] = {false};
     
     while (tttt--) {
         int v1;cin>>v1;
         int v2;cin>>v2;
         int cost;cin>>cost;
         adj[v1 - 1].push_back({v2 -1, cost});
         adj[v2 - 1].push_back({v1 -1, cost});
     }
     
     int totalSum = 0;
     pq.push({0, 0});
     while (!pq.empty()) {
         ii topElem = pq.top();pq.pop();
         if (!visited[topElem.second]) {
             visited[topElem.second] = true;
             totalSum += topElem.first;
             for (auto elem : adj[topElem.second]) {
                 pq.push({elem.second, elem.first});
             }
         }
     }

     cout << totalSum << endl;

     totalSum = 0;
     bool visited2[1000] = {false};
     pq.push({0, 0});
     while (!pq.empty()) {
         ii topElem = pq.top();pq.pop();
         if (!visited2[topElem.second]) {
             visited2[topElem.second] = true;
             totalSum += (-1 * topElem.first);
             for (auto elem : adj[topElem.second]) {
                 pq.push({-elem.second, elem.first});
             }
         }
     }

     cout << totalSum << endl;
 
    return 0;
}
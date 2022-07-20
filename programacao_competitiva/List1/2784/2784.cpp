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
     int islands;cin>>islands;
     int cables;cin>>cables;
     
     vector<ii> adj[1000];
     priority_queue<ii> pq;

     int dist[1000];
     for (int i = 0; i < 1000; i++) { 
         dist[i] = INF;
     }
     while(cables--) {
         int v1;cin>>v1;
         int v2;cin>>v2;
         int cost;cin>>cost;
         adj[v1 - 1].push_back({v2 -1, cost});
         adj[v2 - 1].push_back({v1 -1, cost});
     }
     int server;cin>>server;
     
     pq.push({0, server - 1});
     dist[server - 1] = 0;
     while (!pq.empty()) {
         ii topElem = pq.top();pq.pop();
         for (auto elem : adj[topElem.second]) {
             if (dist[elem.first] > dist[topElem.second] + elem.second) {
                 dist[elem.first] = dist[topElem.second] + elem.second;
                 pq.push({-dist[elem.first], elem.first});
             }
         }
     }
     
     int max_ = -1;
     int min_ = INF;
     for (auto currDis : dist) {
        if (currDis > max_ && currDis != INF) {
            max_ = currDis;
        }
        if (currDis < min_ && currDis > 0) {
            min_ = currDis;
        }
     }
     
     cout << max_ - min_ << endl;
 
    return 0;
}
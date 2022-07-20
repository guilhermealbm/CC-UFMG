#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>

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
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    int n;
    while (cin>>n) {
        vector<ii> adj[1000];
        priority_queue<ii> pq;

        int dist[1000];
        for (int i = 0; i < 1000; i++) { 
            dist[i] = INF;
        }

        int m;cin>>m;
        int k;cin>>k;
        double p;cin>>p;

        vector<ii> pairs;
        for (size_t count = 0; count < m; count++) {
            int i;cin>>i;
            int j;cin>>j;
            pairs.push_back({i, j});
        }

        int a;cin>>a;
        int soldiers[1000] = {0};
        for (size_t i = 0; i < a; i++) {
            int pos;cin>>pos;
            soldiers[pos - 1] += 1;
        }

        for (auto pair = pairs.begin(); pair != pairs.end(); pair++) {
            adj[pair->first - 1].push_back({pair->second -1, soldiers[pair->second - 1]});
            adj[pair->second - 1].push_back({pair->first -1, soldiers[pair->first - 1]});
        }

        int start;cin>>start;
        int end;cin>>end;

        pq.push({soldiers[start - 1], start - 1});
        dist[start - 1] = soldiers[start - 1];

        while (!pq.empty()) {
            ii topElem = pq.top();pq.pop();
            for (auto elem : adj[topElem.second]) {
                if (dist[elem.first] > dist[topElem.second] + elem.second) {
                    dist[elem.first] = dist[topElem.second] + elem.second;
                    pq.push({-dist[elem.first], elem.first});
                }
            }
        }

        int totalSoldiers = dist[end - 1];
        if (totalSoldiers > k) {
            cout << "0.000" << endl;
        } else {
            cout << fixed << setprecision(3) << pow(p, totalSoldiers) << endl;
        }

    }

    return 0;
}
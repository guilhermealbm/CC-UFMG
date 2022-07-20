#include <iostream>
#include <vector>
#include <queue>
#include <map>
 
using namespace std;

struct dinic {
    struct edge {
        int to, cap, rev, flow;
        bool res;
        edge(int to_, int cap_, int rev_, bool res_)
            : to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
    };
 
    vector<vector<edge>> g;
    vector<int> lev, beg;
    long long F;
    dinic(int n) : g(n), F(0) {}
 
    void add(int a, int b, int c) {
        g[a].emplace_back(b, c, g[b].size(), false);
        g[b].emplace_back(a, 0, g[a].size()-1, true);
    }
    bool bfs(int s, int t) {
        lev = vector<int>(g.size(), -1); lev[s] = 0;
        beg = vector<int>(g.size(), 0);
        queue<int> q; q.push(s);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (auto& i : g[u]) {
                if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
                lev[i.to] = lev[u] + 1;
                q.push(i.to);
            }
        }
        return lev[t] != -1;
    }
    int dfs(int v, int s, int f = 0x3f3f3f3f) {
        if (!f or v == s) return f;
        for (int& i = beg[v]; i < g[v].size(); i++) {
            auto& e = g[v][i];
            if (lev[e.to] != lev[v] + 1) continue;
            int foi = dfs(e.to, s, min(f, e.cap - e.flow));
            if (!foi) continue;
            e.flow += foi, g[e.to][e.rev].flow -= foi;
            return foi;
        }
        return 0;
    }
    long long max_flow(int s, int t) {
        while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
        return F;
    }
};
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    map<string, int> myMap = {{"XXL", 0}, {"XL", 1}, {"L", 2}, {"M", 3}, {"S", 4}, {"XS", 5}};
    int tttt; cin >> tttt;
    while(tttt--) {
        int n, m; cin >> n; cin >> m;
        dinic D(n + m + 2);

        for (size_t i = 1; i < m + 1; i++)
            D.add(0, i, 1);

        for (size_t i = m + 1; i < m + n + 1; i++)
            D.add(i, (n + m + 1), 1);
        
        for (size_t i = 1; i < m + 1; i++) {
            string size1; cin >> size1;
            string size2; cin >> size2;
            for (size_t j = m + 1; j < m + n + 1; j+=6) {
                D.add(i, j + myMap[size1], 1);
                D.add(i, j + myMap[size2], 1);
            }
            
        }

        int flow = D.max_flow(0, n + m + 1);
        if (flow == m)
            cout << "YES" << endl;
        else 
            cout << "NO" << endl;
        
    }

 
    return 0;
}
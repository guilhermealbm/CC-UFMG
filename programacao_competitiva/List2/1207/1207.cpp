#include <iostream>
#include <vector>
#include <queue>
#include <map>

#define INF 0x3f3f3f3f
 
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

    int n, m;
    while (cin >> n >> m) {

        int array[400] = {0};
        int sum = 0;
        dinic D(n + m + 2);

        for (int i = 0; i < n; i++) {
            int c; cin >> c;
            D.add(0, i + 1, c);
        }

        for (int i = 0; i < m; i++) {
            int p; cin >> p;
            array[i] = p;
        }

        for (int i = 0; i < m; i++) {
            int b; cin >> b;
            sum += b;
            D.add(n + i + 1, n + m + 1, b);
            for (int j = 0; j < array[i]; j++) {
                int curr; cin >> curr;
                D.add(curr, n + i + 1, INF);
            }
        }

        cout << sum - D.max_flow(0, n + m + 1) << endl;
    }
 
    return 0;
}

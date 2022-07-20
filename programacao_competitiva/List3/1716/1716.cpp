#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;


#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;
typedef pair<int, int> ii;

ll x, y, d;

void mdc(int a, int b) {
    if (!b) {
        x = 1; y = 0; d = a; return;
    }

    mdc(b, a % b);
    ll x_ = y;
    ll y_ = x - (a / b) * y;
    x = x_;
    y = y_;
}


int main(){ _
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    ll n; cin >> n;
    ll e; cin >> e;
    ll c; cin >> c;

    ll origN = n;

    ll tot = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n = n / i;
            }

            tot -= tot / i;
        }
    }
    
    if (n > 1) {
        tot -= tot / n;
    }

    mdc(e, tot);
    d = (x % tot + tot) % tot;

    ll ans = 1;
    while (d) {
        if (d & 1) {
            ans = (ans * c) % origN;
        }

        c = (c * c) % origN;
        d >>= 1;
    }

    cout << ans << endl;
    
 
    return 0;
}
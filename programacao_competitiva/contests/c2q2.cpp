//#include <bits/stdc++.h>

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


int main(){ _

    string s1, s2;

    cin >> s1; cin >> s2;

    int i = 0;
    int j = 0;
    int k = 0;
    int ans = 0;

    while (i < s1.size()) {
        j = 0;
        if (s1[i] == s2[j]) {
            k = i;
            while (k < s1.size() && j < s2.size() && s1[k] == s2[j]) {
                k++;
                j++;
            }

            if(j >= s2.size()) {
                i = k;
                ans++;
            } else {
                i++;
            }
        } else {
            i++;
        }
    }

    cout << ans << endl;

	exit(0);
}


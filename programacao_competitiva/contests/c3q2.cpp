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
//	char end = '\n';
	int tttt;cin>>tttt;
	while (tttt--)
	{
        string input; cin >> input;
        set<char> mem;
        int days = 1;
        for (int i = 0; i < input.size(); i++) {
            auto it = mem.find(input[i]);
            if (it == mem.end()) { // not in set
                if (mem.size() < 3) {
                    mem.insert(input[i]);
                } else {
                    mem.clear();
                    days++;
                    mem.insert(input[i]);
                }
            }
        }
        cout << days << endl;
	}

	exit(0);
}

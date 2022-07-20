#include <iostream>
 
using namespace std;
 
int main() {

    while (true) {
        int n, k; cin >> n; cin >> k;
        if (n == 0 && k == 0) {
            break;
        }

        int array[10001] = {0};
        long long dp[101][101] = {0};

        for (int i = 1; i <= n; i++) {
            int num; cin >> num;
            array[i] = num;
            dp[i][1] = 1;
        }

        for (int i = 2; i <= n; i++) {
            for (int j = 2; j <= k; j++) {
                for (int k = 1; k < i; k++) {
                    if (array[i] > array[k])
                        dp[i][j] += dp[k][j - 1];
                }
            }
        }

        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += dp[i][k];
        }

        cout << ans << endl;

    }
 
    return 0;
}
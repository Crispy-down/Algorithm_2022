#include <bits/stdc++.h>
using namespace std;

int n,k;
int dp[305][25]; // dp[N][K] = P(N,K);


int solve(int N,int K) {
    if(N < K) {
        return dp[N][K] = 0;
    }

    if(N == K || K == 1) {
        return dp[N][K] = 1;
    }

    int ans = dp[N][K];
    if(ans != -1) {
        return dp[N][K];
    }

    if(N > K) {
        dp[N][K] = (solve(N-1,K-1) % 1000000007) + (solve(N-K,K) % 1000000007);
    }

    return dp[N][K] %= 1000000007;
}

int main() {
    ifstream fin("addingways.inp");
    ofstream fout("addingways.out");


    memset(dp,-1,sizeof(dp));

    while(true) {
        fin >> n >> k;

        if(n == 0 && k == 0) {
            break;
        }
        else if(k == 1 || n == k) {
            fout << 1 << '\n';
            continue;
        }
        else if(n < k) {
            fout << 0 << '\n';
            continue;
        }

        solve(n,k);

        fout << dp[n][k] << '\n';   

        memset(dp,-1,sizeof(dp));
    }


    fin.close();
    fout.close();

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
const int MIN = INT_MIN;

int T;
int N;
int board[1002];
int dp[1002];
int ans;

int solve(int N) { // dp[1] , dp[2] , dp[3] 테이블 안에 최대값을 저장한다.
// return => N index에 대한 dp 테이블의 최댓값.
    if(N == 1 || N == 2 || N == 3) {
        //dp ?
        return board[N];
    }
    if(N <= 0) {
        return 0;
    }

    int n2;
    int n3;
    int n4;

    n2 = solve(N-2) + board[N]; // 해당 N idx 안 값 더하기 + N-2 칸 전까지의 합
    n3 = solve(N-3) + board[N];
    n4 = solve(N-4) + board[N];

    dp[N] = max({n2,n3,n4});

    // dp[N-2] = max(dp[N-2],n2); // 원래 있던 값보다 크면 재정의(최대값 넣기)
    // dp[N-3] = max(dp[N-3],n3);
    // dp[N-4] = max(dp[N-4],n4);

    return dp[N];
}

int main() {
    ifstream fin("card.inp");
    ofstream fout("card.out");

    memset(dp,-1000,sizeof(dp));

    cin >> T;

    while(T--) {
        cin >> N;
        for(int i = 1;i<=N;i++) {
            cin >> board[i];
        }
        // dp[N] = board[N]; // initialize
        solve(N);
        for(int i = 1;i<=N;i++) {
            cout << dp[i] << " ";
        }
    }




    fin.close();
    fout.close();

    return 0;
}
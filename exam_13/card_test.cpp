#include <bits/stdc++.h>
using namespace std;

int T;
int N;
int board[1010];
int dp[3][1010];
queue <int> q;

void reset() {
    for(int i = 0;i<3;i++) {
        for(int j = 1;j<1010;j++) {
            dp[i][j] = -1000000;
        }
    }
}

void solve() {
    // dp 1 기준부터 시작.
    // N + 3 , N + 4 값만 저장.
    q.push(1);
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        for(int nxt : {cur + 3 , cur + 4}) {
            if(dp[0][nxt] != -1000000) { // 방문한거는 안넣음
                continue;
            }
            if(nxt == N - 1) {
                continue;
            }
            if(nxt > N) {
                continue;
            }
            dp[0][nxt] = max(dp[0][nxt],dp[0][cur] + board[nxt]);
            q.push(nxt);
        }
    }
}

void solve2() {
    // dp 2 , 3 기준부터 시작.
    // 초기값 => N+2,N+3,N+4
    // N + 3 , N + 4 값만 저장.
    q.push(2);
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        for(int nxt : {cur + 2, cur + 3 , cur + 4}) {
            if(dp[1][nxt] != -1000000) {
                continue;
            }
            if(nxt == N - 1) {
                continue;
            }
            if(nxt > N) {
                continue;
            }
            dp[1][nxt] = max(dp[1][nxt],dp[1][cur] + board[nxt]);
            q.push(nxt);
        }
    }
}

void solve3() {
    // dp 2 , 3 기준부터 시작.
    // 초기값 => N+2,N+3,N+4
    // N + 3 , N + 4 값만 저장.
    q.push(3);
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        for(int nxt : {cur + 2,cur + 3 , cur + 4}) {
            if(dp[2][nxt] != -1000000) {
                continue;
            }
            if(nxt == N - 1) {
                continue;
            }
            if(nxt > N) {
                continue;
            }
            dp[2][nxt] = max(dp[2][nxt],dp[2][cur] + board[nxt]);
            q.push(nxt);
        }
    }
}


int main() {
    ifstream fin("card.inp");
    ofstream fout("card.out");

    cin >> T;
    while(T--) {
        reset();

        cin >> N;
        for(int i = 1;i<=N;i++) {
            cin >> board[i];
        }

        dp[0][1] = board[1];
        dp[1][2] = board[2];
        dp[2][3] = board[3];

        solve();
        solve2();
        solve3();

        cout << dp[0][N] << '\n';
        cout << dp[1][N] << '\n';
        cout << dp[2][N] << '\n';

        cout << max({dp[0][N],dp[1][N],dp[2][N]}) << '\n';
    }

    fin.close();
    fout.close();


    return 0;
}
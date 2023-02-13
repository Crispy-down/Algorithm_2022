#include <bits/stdc++.h>
using namespace std;

int T;
int N;
int board[1002];
int dp[1002];
int route[1002];
int ans[3];

void reset() {
    for(int i = 1;i<=1001;i++) {
        dp[i] = 0;
        route[i] = 0;
    }
}

int max_cnt(int cur) { // 최대값이 어디서 왔는지, 경로 저장 및 무슨 값을 저장해야하는지 인덱스 반환.
    int temp = -1000000;
    int idx;

    for(int i = 2;i<=4;i++) {
        if(cur == 4 && i == 4) {
            continue;
        }
        if(temp < dp[cur - i] + board[cur]) { // 최댓값 뽑아냄
            temp = dp[cur - i] + board[cur]; // 갱신
            idx = cur - i; // 최댓값에 대한 인덱스
        }
    }

    route[cur] = idx; // 경로 추적용 인덱스 저장

    return temp; // 최댓값 반환
}

void solve() {
    for(int i = 4;i<=N-1;i++) { // N-1 칸까지의 최댓값과 그에 대한 경로 저장.
        dp[i] = max_cnt(i);
        // dp[i] = max(dp[i-2] + board[i] , dp[i-3] + board[i] , dp[i-4] + board[i]);
    } // N칸에 대해서 값 3개 존재. => 경로 판별 필요.  
}

void check_legit(int idx) { // N칸에 대한 3개의 값중 경로가 유효한 값을 뽑아냄.(결국엔 최댓값을 뽑아냄)
// idx = 2, 3, 4
    vector <int> way;


    way.push_back(N);
    way.push_back(N - idx);

    int nxt = N - idx;
    int cur;

    while(true) {
        cur = route[nxt];
        if(cur == 1 || cur == 2 || cur == 3) {
            way.push_back(cur);
            break;
        }
        if(cur == -1) {
            break;
        }
        way.push_back(cur);
        nxt = cur;
    } // 경로 벡터안에 다 존재.

    // 유효한 경로인지 판단.

    // for(int i = 0;i<way.size();i++) {
    //     cout << way[i] << " ";
    // }

    // cout << '\n';

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

        dp[1] = board[1];
        dp[2] = board[2];
        dp[3] = board[3];

        solve();

        route[1] = -1;
        route[2] = -1;
        route[3] = -1;

        ans[0] = dp[N-2] + board[N]; // idx = N-2, N
        ans[1] = dp[N-3] + board[N]; // idx = N-3, N
        if(N > 4) {
            ans[2] = dp[N-4] + board[N]; // idx = N-4, N
        }

        cout << ans[0] << " " << ans[1] << " " << ans[2] << '\n';

        // for(int i = 2;i<=4;i++) {
        //     if(N == 4 && i == 4) {
        //         continue;
        //     }
        //     check_legit(i); // 3번 돌려서 유효한 경로만 뽑아냄
        // }
        // 불값 true인 애들 중
        // 최댓값이 정답.
    }



    fin.close();
    fout.close();

    return 0;
}

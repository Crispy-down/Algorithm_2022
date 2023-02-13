#include <bits/stdc++.h>
#define INF 0xfffffff
using namespace std;

int T;
int M,N,L,G; // M x N , seg cost , fuel cost
int use_G; // 이때까지 쓴 연료의 양
int ans_L; // 이때까지 지난 시간
int max_turn;
int turn_range;

int dp[102][102][202][2]; 
// dp[i][j][t][d] = (i,j) 칸에서의 몇 번의 (t)urn을 한 상태였을 때 *d(d == 0 왼쪽에서 1이면 위에서 온 경우) 걸린 연료의 양

int main() {
    cin >> T;
    while(T--) {
        int row[102][102];
        int col[102][102];
        cin >> M >> N >> L >> G;
        for(int i = 0;i<M;i++) {
            for(int j = 1;j<N;j++) {
                cin >> row[i][j];
            }
        }
        for(int i = 1;i<M;i++) {
            for(int j = 0;j<N;j++) {
                cin >> col[i][j];
            }
        }
        if(M < N) {
            max_turn = 2 * M;
        }
        else {
            max_turn = 2 * N;
        }
        for(int i = 0;i<M;i++) {
            for(int j = 0;j<N;j++) {
                for(int t = 0;t<=max_turn;t++) {
                    dp[i][j][t][0] = INF;
                    dp[i][j][t][1] = INF;
                }
            }
        }

        dp[0][0][0][0] = 0;
        dp[0][0][0][1] = 0;
        for(int i = 1;i<M;i++) {
            dp[i][0][0][1] = col[i][0] + dp[i-1][0][0][1];
        }
        for(int i = 1;i<N;i++) {
            dp[0][i][0][0] = row[0][i] + dp[0][i-1][0][0];
        }

        for(int i = 1;i<M;i++) {
            for(int j = 1;j<N;j++) {
                if(i < j) {
                    turn_range = i*2;
                }
                else {
                    turn_range = j*2;
                }
                for(int t = 1;t<=turn_range;t++) {
                    // d == 0 => 오른쪽에서 온 경우 
                    if(dp[i][j-1][t][0] < dp[i][j-1][t-1][1]) { // 이전 오른쪽 칸에서 오른쪽으로 왔을때의 연료합이 윗쪽에서 온 연료합보다 작은 경우
                        dp[i][j][t][0] = dp[i][j-1][t][0] + row[i][j]; // 오른쪽으로 왔을 때의 연료합을 선택
                    }
                    else { // 이전 오른쪽 칸에서 오른쪽으로 왔을때의 연료합이 윗쪽에서 온 연료합보다 큰 경우
                        dp[i][j][t][0] = dp[i][j-1][t-1][1] + row[i][j]; // 윗쪽에서 왔을 때의 연료합을 선택 (방향 전환 때문에 t 증가)
                    }
                    // d == 1 => 윗쪽에서 온 경우
                    if(dp[i-1][j][t-1][0] < dp[i-1][j][t][1]) { // 이전 윗칸에서 오른쪽에서 왔을때의 연료합이 윗쪽에서 온 연료합보다 작은 경우
                        dp[i][j][t][1] = dp[i-1][j][t-1][0] + col[i][j]; // 오른쪽에서 왔을 때의 연료합을 선택 (방향 전환 때문에 t 증가)
                    } 
                    else { // 이전 윗칸에서 오른쪽에서 왔을때의 연료합이 윗쪽에서 온 연료합보다 큰 경우
                        dp[i][j][t][1] = dp[i-1][j][t][1] + col[i][j]; // 윗쪽에서 왔을 때의 연료합을 선택 
                    }
                }
            }
        }

        bool legit = false;
        
        for(int t = 0;t<=max_turn;t++) {
            if(dp[M-1][N-1][t][0] <= G || dp[M-1][N-1][t][1] <= G) { // M-1,N-1 칸에서 연료량이 G 이하일 때
                legit = true;
                cout << L * (N + M -2) + t << '\n'; // 시간 출력
                break; 
            }
        }
        if(!legit) {
            cout << "-1" << '\n';
        }

    }
}
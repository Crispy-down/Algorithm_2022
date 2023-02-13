#include <bits/stdc++.h>
using namespace std;
// Alice는 양끝에서 최대가 되는 카드를 가져간다.
// 컴퓨터는 양끝에서 최대가 되는 카드를 가져간다.
// == 컴퓨터는 다음턴(앨리스)일때 최소가 되도록 카드를 가져간다.

int T,N;
int board[1002];
int dp[1002][1002]; // dp[i][j] => i ~ j 카드가 있을 때 Alice가 얻는 최대 점수
// Alice가 뽑는 턴 == 1

int solve(int turn,int front,int rear) { 
    if(front > rear) { // break point
        return 0;
    }

    if(dp[front][rear]) { // 중복계산 방지 
        return dp[front][rear];
    }

    if(turn == 1) { // 앨리스 턴일 때
        return dp[front][rear] = max(solve(0,front + 1,rear) + board[front],solve(0,front,rear - 1) + board[rear]);
        // 앨리스가 왼쪽카드를 가져갔을 때 / 앨리스가 오른쪽 카드를 가져갔을 때 => 최댓값
    }
    else { // 컴퓨터 턴일 때
        return dp[front][rear] = min(solve(1,front+1,rear),solve(1,front,rear-1));
    } // 앨리스 턴일때의 최솟값(앨리스가 왼쪽 카드를 가져갔을 때 / 앨리스가 오른쪽 카드를 가져갔을 때)


}

int main() {
    ifstream fin("card.inp");
    ofstream fout("card.out");
    fin >> T;

    while(T--) {
        fin >> N;
        for(int i = 0;i<N;i++) {
            fin >> board[i];
        }
        solve(1,0,N-1); // Alice 턴 시작 / 0 ~ N-1
        fout << dp[0][N-1] << '\n';

        memset(dp,0,sizeof(dp));
    }

    fin.close();
    fout.close();
    return 0;
}
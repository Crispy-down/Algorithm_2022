#include <bits/stdc++.h>
using namespace std;
// Alice�� �糡���� �ִ밡 �Ǵ� ī�带 ��������.
// ��ǻ�ʹ� �糡���� �ִ밡 �Ǵ� ī�带 ��������.
// == ��ǻ�ʹ� ������(�ٸ���)�϶� �ּҰ� �ǵ��� ī�带 ��������.

int T,N;
int board[1002];
int dp[1002][1002]; // dp[i][j] => i ~ j ī�尡 ���� �� Alice�� ��� �ִ� ����
// Alice�� �̴� �� == 1

int solve(int turn,int front,int rear) { 
    if(front > rear) { // break point
        return 0;
    }

    if(dp[front][rear]) { // �ߺ���� ���� 
        return dp[front][rear];
    }

    if(turn == 1) { // �ٸ��� ���� ��
        return dp[front][rear] = max(solve(0,front + 1,rear) + board[front],solve(0,front,rear - 1) + board[rear]);
        // �ٸ����� ����ī�带 �������� �� / �ٸ����� ������ ī�带 �������� �� => �ִ�
    }
    else { // ��ǻ�� ���� ��
        return dp[front][rear] = min(solve(1,front+1,rear),solve(1,front,rear-1));
    } // �ٸ��� ���϶��� �ּڰ�(�ٸ����� ���� ī�带 �������� �� / �ٸ����� ������ ī�带 �������� ��)


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
        solve(1,0,N-1); // Alice �� ���� / 0 ~ N-1
        fout << dp[0][N-1] << '\n';

        memset(dp,0,sizeof(dp));
    }

    fin.close();
    fout.close();
    return 0;
}
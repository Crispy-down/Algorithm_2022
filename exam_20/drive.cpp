#include <bits/stdc++.h>
#define INF 0xfffffff
using namespace std;

int T;
int M,N,L,G; // M x N , seg cost , fuel cost
int use_G; // �̶����� �� ������ ��
int ans_L; // �̶����� ���� �ð�
int max_turn;
int turn_range;

int dp[102][102][202][2]; 
// dp[i][j][t][d] = (i,j) ĭ������ �� ���� (t)urn�� �� ���¿��� �� *d(d == 0 ���ʿ��� 1�̸� ������ �� ���) �ɸ� ������ ��

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
                    // d == 0 => �����ʿ��� �� ��� 
                    if(dp[i][j-1][t][0] < dp[i][j-1][t-1][1]) { // ���� ������ ĭ���� ���������� �������� �������� ���ʿ��� �� �����պ��� ���� ���
                        dp[i][j][t][0] = dp[i][j-1][t][0] + row[i][j]; // ���������� ���� ���� �������� ����
                    }
                    else { // ���� ������ ĭ���� ���������� �������� �������� ���ʿ��� �� �����պ��� ū ���
                        dp[i][j][t][0] = dp[i][j-1][t-1][1] + row[i][j]; // ���ʿ��� ���� ���� �������� ���� (���� ��ȯ ������ t ����)
                    }
                    // d == 1 => ���ʿ��� �� ���
                    if(dp[i-1][j][t-1][0] < dp[i-1][j][t][1]) { // ���� ��ĭ���� �����ʿ��� �������� �������� ���ʿ��� �� �����պ��� ���� ���
                        dp[i][j][t][1] = dp[i-1][j][t-1][0] + col[i][j]; // �����ʿ��� ���� ���� �������� ���� (���� ��ȯ ������ t ����)
                    } 
                    else { // ���� ��ĭ���� �����ʿ��� �������� �������� ���ʿ��� �� �����պ��� ū ���
                        dp[i][j][t][1] = dp[i-1][j][t][1] + col[i][j]; // ���ʿ��� ���� ���� �������� ���� 
                    }
                }
            }
        }

        bool legit = false;
        
        for(int t = 0;t<=max_turn;t++) {
            if(dp[M-1][N-1][t][0] <= G || dp[M-1][N-1][t][1] <= G) { // M-1,N-1 ĭ���� ���ᷮ�� G ������ ��
                legit = true;
                cout << L * (N + M -2) + t << '\n'; // �ð� ���
                break; 
            }
        }
        if(!legit) {
            cout << "-1" << '\n';
        }

    }
}
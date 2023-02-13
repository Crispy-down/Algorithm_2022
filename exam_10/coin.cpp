#include <bits/stdc++.h>
using namespace std;

int T;
int a,b,c;
bool dp[102][102][102]; // 돌이 A B C 개 남아있을 때, Alice가 이길 수 있는가?

int main() {
    ifstream fin("coin.inp");
    ofstream fout("coin.out");

// 마지막에 코인을 가져가는 사람이 짐.

    dp[1][0][0] = false;
    dp[0][1][0] = false;
    dp[0][0][1] = false;

    dp[1][1][0] = true;
    dp[1][0][1] = true;
    dp[0][1][1] = true;

    dp[1][1][1] = false;

    dp[2][0][0] = true;
    dp[0][2][0] = true;
    dp[0][0][2] = true;

    dp[2][2][0] = false;
    dp[2][0][2] = false;
    dp[0][2][2] = false;

    dp[2][2][2] = true;

    dp[3][0][0] = true;
    dp[0][3][0] = true;
    dp[0][0][3] = true;

    dp[3][3][0] = true;
    dp[0][3][3] = true;
    dp[3][0][3] = true;

    dp[3][3][3] = 


    for(int i = 4;i<=100;i++) {
        for(int j = 4;j<=100;j++) {
            for(int k = 4;k<=100;k++) {
                dp[k][j][i] = !dp[k-1][j][i] || !dp[k-2][j][i] || !dp[k-3][j][i];
                dp[j][k][i] = !dp[j][k-1][i] || !dp[j][k-2][i] || !dp[j][k-3][i];
                dp[j][i][k] = !dp[j][i][k-1] || !dp[j][i][k-2] || !dp[j][i][k-3];

            }
        }
    }


    cin >> T;

    while(T--) {
        cin >> a >> b >> c;


        cout << "(" << a << " " << b << " " << c << ") :" << '\n';
    }




    fin.close();
    fout.close();

    return 0;
}
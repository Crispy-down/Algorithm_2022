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

int max_cnt(int cur) { // �ִ밪�� ��� �Դ���, ��� ���� �� ���� ���� �����ؾ��ϴ��� �ε��� ��ȯ.
    int temp = -1000000;
    int idx;

    for(int i = 2;i<=4;i++) {
        if(cur == 4 && i == 4) {
            continue;
        }
        if(temp < dp[cur - i] + board[cur]) { // �ִ� �̾Ƴ�
            temp = dp[cur - i] + board[cur]; // ����
            idx = cur - i; // �ִ񰪿� ���� �ε���
        }
    }

    route[cur] = idx; // ��� ������ �ε��� ����

    return temp; // �ִ� ��ȯ
}

void solve() {
    for(int i = 4;i<=N-1;i++) { // N-1 ĭ������ �ִ񰪰� �׿� ���� ��� ����.
        dp[i] = max_cnt(i);
        // dp[i] = max(dp[i-2] + board[i] , dp[i-3] + board[i] , dp[i-4] + board[i]);
    } // Nĭ�� ���ؼ� �� 3�� ����. => ��� �Ǻ� �ʿ�.  
}

void check_legit(int idx) { // Nĭ�� ���� 3���� ���� ��ΰ� ��ȿ�� ���� �̾Ƴ�.(�ᱹ�� �ִ��� �̾Ƴ�)
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
    } // ��� ���;ȿ� �� ����.

    // ��ȿ�� ������� �Ǵ�.

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
        //     check_legit(i); // 3�� ������ ��ȿ�� ��θ� �̾Ƴ�
        // }
        // �Ұ� true�� �ֵ� ��
        // �ִ��� ����.
    }



    fin.close();
    fout.close();

    return 0;
}

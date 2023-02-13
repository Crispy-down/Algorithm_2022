#include <bits/stdc++.h>
using namespace std;
const int MAX = 0x3f3f3f3f;

int T;
int W,L,H;
int dp[202][202][202]; // W, L, H 일때 최소 절단으로 만들어지는 조각 수

int solve(int w,int l,int h) {
    if(w == l && l == h) { // base condition
        return 1;
    }

    if(w == 1 || h == 1 || l == 1) { // w,h,l 축 중 하나라도 1이 된다면
        return w * l * h; // 1씩 다 자르면 정육면체 개수 구하기 가능
    }

    int ans = dp[w][l][h];
    if(ans != -1) { // 값이 있다면 top-down 필요 xxx
        return ans;
    }

    int cnt_w = MAX;
    int cnt_l = MAX;
    int cnt_h = MAX;

    for(int i = 1;i<w/2 + 1;i++) {
        cnt_w = min(cnt_w,solve(i,l,h) + solve(w - i,l,h)); // w 축 기준
    }
    for(int i = 1;i<l/2 + 1;i++) {
        cnt_l = min(cnt_l,solve(w,i,h) + solve(w,l - i,h)); // l 축 기준
    }
    for(int i = 1;i<h/2 + 1;i++) {
        cnt_h = min(cnt_h,solve(w,l,i) + solve(w,l,h - i)); // h 축 기준
    }

    cnt_w = min(cnt_w,cnt_l);
    ans = min(cnt_w,cnt_h); // 가장 최소의 절단으로 만들어진 개수

    dp[w][l][h] = ans;
    dp[w][h][l] = ans;
    dp[l][w][h] = ans;
    dp[l][h][w] = ans;
    dp[h][w][l] = ans;
    dp[h][l][w] = ans; // 다 같은 케이스.

    return ans;
}

int main() {
    ifstream fin("cube.inp");
    ofstream fout("cube.out");

    memset(dp,-1,sizeof(dp)); // initialize

    fin >> T;

    while(T--) { // Top-down
        fin >> W >> L >> H;
        fout << solve(W,L,H) << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}
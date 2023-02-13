#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

char input_mode;
int board[202][202];
int N,M;
int dir = 0;
string bitmap;
string ans = "";

void clear(int a,int b) { // initialize.
    for(int i = 0;i<a;i++) {
        for(int j = 0;j<b;j++) {
            board[i][j] = -1;
        }
    }
    ans = "";
    dir = 0;
    bitmap = "";
}

void solve_1(int x,int y,int n,int m) { // 시작좌표 x 값 / y값 / x좌표 움직일 범위 / y좌표 움직일 범위
    if(n == 1 && m == 1) { // base condition
        ans += to_string(board[x][y]);
        return;
    }
    else if(n == 0 || m == 0) { // 해당 범위 존재하지 않음.
        return;
    }

    bool OnlyZero,OnlyOne;
    OnlyOne = OnlyZero = true;

    for(int i = x;i<x + n;i++) {
        for(int j = y;j<y + m;j++) {
            if(board[i][j] == 0) { // 1으로 이루어진 범위의 composition이 아님.
                OnlyOne = false;
            }
            if(board[i][j] == 1) { // 0으로 이루어진 범위의 composition이 아님.
                OnlyZero = false;
            }  
        }
    }

    if(OnlyZero == true) { // 0으로만 이루어진 composition
        ans += "0";
        return;
    }
    if(OnlyOne == true) { // 1으로만 이루어진 composition
        ans += "1";
        return;
    }

    // decompostion(0이나 1로만 이루어지지 않았을 때.)
    if(n % 2 == 0 && m % 2 == 0) {
        ans += "D";
        solve_1(x, y, n/2, m/2); // 좌상단
        solve_1(x, y+m/2, n/2, m/2); // 우상단
        solve_1(x+n/2, y, n/2, m/2); // 좌하단
        solve_1(x+n/2, y+m/2, n/2, m/2); // 우하단
        // N,M 짝수일때만 해당
    }
    else if(n % 2 != 0 && m % 2 == 0) {
        ans += "D";
        solve_1(x, y, n/2 + 1, m/2); // 좌상단
        solve_1(x, y+m/2, n/2 + 1 , m/2); // 우상단
        solve_1(x+n/2 + 1, y, n/2, m/2); // 좌하단
        solve_1(x+n/2 + 1, y+m/2, n/2, m/2); // 우하단
        // N 홀수 M 짝수
    }
    else if(n % 2 == 0 && m % 2 != 0) {
        ans += "D";
        solve_1(x, y, n/2, m/2 + 1); // 좌상단
        solve_1(x, y+m/2 + 1, n/2, m/2); // 우상단
        solve_1(x+n/2, y, n/2, m/2 + 1); // 좌하단
        solve_1(x+n/2, y+m/2 + 1, n/2, m/2); // 우하단
        // N 짝수 M 홀수
    }
    else if(n % 2 != 0 && m % 2 != 0) {
        ans += "D";
        solve_1(x, y, n/2 + 1, m/2 + 1); // 좌상단
        solve_1(x, y + m/2 + 1, n/2 + 1, m/2); // 우상단
        solve_1(x+n/2 + 1, y, n/2, m/2 + 1); // 좌하단
        solve_1(x+n/2 + 1, y+m/2 + 1, n/2, m/2); // 우하단
        // N 홀수 M 홀수
    }
}

void solve_2(int x,int y,int n,int m) {
    if(dir >= bitmap.size()) {
        return;
    }
    char cmd = bitmap[dir]; // 매 loop마다 dir 값 +1, cmd 값에 따라 변경.
    
    if(n == 0 || m == 0) {
        return;
    }

    if(cmd == 'D') {
        if(n % 2 == 0 && m % 2 == 0) {
            dir++;
            solve_2(x, y, n/2, m/2); // 좌상단
            solve_2(x, y+m/2, n/2, m/2); // 우상단
            solve_2(x+n/2, y, n/2, m/2); // 좌하단
            solve_2(x+n/2, y+m/2, n/2, m/2); // 우하단
            // N,M 짝수일때만 해당
        }
        else if(n % 2 != 0 && m % 2 == 0) {
            dir++;
            solve_2(x, y, n/2 + 1, m/2); // 좌상단
            solve_2(x, y+m/2, n/2 + 1 , m/2); // 우상단
            solve_2(x+n/2 + 1, y, n/2, m/2); // 좌하단
            solve_2(x+n/2 + 1, y+m/2, n/2, m/2); // 우하단
            // N 홀수 M 짝수
        }
        else if(n % 2 == 0 && m % 2 != 0) {
            dir++;
            solve_2(x, y, n/2, m/2 + 1); // 좌상단
            solve_2(x, y+m/2 + 1, n/2, m/2); // 우상단
            solve_2(x+n/2, y, n/2, m/2 + 1); // 좌하단
            solve_2(x+n/2, y+m/2 + 1, n/2, m/2); // 우하단
            // N 짝수 M 홀수
        }
        else if(n % 2 != 0 && m % 2 != 0) {
            dir++;
            solve_2(x, y, n/2 + 1, m/2 + 1); // 좌상단
            solve_2(x, y + m/2 + 1, n/2 + 1, m/2); // 우상단
            solve_2(x+n/2 + 1, y, n/2, m/2 + 1); // 좌하단
            solve_2(x+n/2 + 1, y+m/2 + 1, n/2, m/2); // 우하단
            // N 홀수 M 홀수
        } 
    }
    else if(cmd == '1') {
        for(int i = x;i<x+n;i++) {
            for(int j = y;j<y+m;j++) {
                board[i][j] = 1;
            }
        }
        dir++;
        return;
    }
    else if(cmd == '0') {
        for(int i = x;i<x+n;i++) {
            for(int j = y;j<y+m;j++) {
                board[i][j] = 0;
            }
        }
        dir++;
        return;
    }
}



int main() {
    ifstream fin("bitmap.inp");
    ofstream fout("bitmap.out");

    while(true) {
        fin >> input_mode;

        if(input_mode == '#') {
            break;
        }
        else if(input_mode == 'B') { // 주어진 비트맵을 가지고, 비트맵 decomposition
            fin >> N >> M;

            string ttmp;
            while(true) {
                fin >> ttmp;
                bitmap += ttmp;
                if(ttmp.size() < 50) {
                    break;
                }
            }
            
            int temp = 0;
            for(int i = 0;i<N;i++) {
                temp = i*M;
                for(int j = 0;j<M;j++) {
                    board[i][j] = bitmap[temp + j] - '0';
                }
            }

            solve_1(0,0,N,M);

            fout << "D" << setw(4) << N << setw(4) << M << '\n';

            for(int i = 0;i<ans.size();i++) {
                if(i != 0 && (i % 50) == 0) {
                    fout << '\n';
                }
                fout << ans[i];
            }
            fout << '\n';
            
        }
        else if(input_mode == 'D') { // 주어진 연산을 가지고, 비트맵을 만들어야함.
            fin >> N >> M;
            string tttmp;
            while(true) {
                fin >> tttmp;
                bitmap += tttmp;
                if(tttmp.size() < 50) {
                    break;
                }
            }

            solve_2(0,0,N,M);

            for(int i = 0;i<N;i++) {
                for(int j = 0;j<M;j++) {
                    ans += to_string(board[i][j]);
                }
            }

            fout << "B" << setw(4) << N << setw(4) << M << '\n';

            for(int i = 0;i<ans.size();i++) {
                if(i != 0 && (i % 50) == 0) {
                    fout << '\n';
                }
                fout << ans[i];
            }
            fout << '\n';
        }

        clear(N,M);
    }


    fin.close();
    fout.close();

    return 0;
}
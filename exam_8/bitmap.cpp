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

void solve_1(int x,int y,int n,int m) { // ������ǥ x �� / y�� / x��ǥ ������ ���� / y��ǥ ������ ����
    if(n == 1 && m == 1) { // base condition
        ans += to_string(board[x][y]);
        return;
    }
    else if(n == 0 || m == 0) { // �ش� ���� �������� ����.
        return;
    }

    bool OnlyZero,OnlyOne;
    OnlyOne = OnlyZero = true;

    for(int i = x;i<x + n;i++) {
        for(int j = y;j<y + m;j++) {
            if(board[i][j] == 0) { // 1���� �̷���� ������ composition�� �ƴ�.
                OnlyOne = false;
            }
            if(board[i][j] == 1) { // 0���� �̷���� ������ composition�� �ƴ�.
                OnlyZero = false;
            }  
        }
    }

    if(OnlyZero == true) { // 0���θ� �̷���� composition
        ans += "0";
        return;
    }
    if(OnlyOne == true) { // 1���θ� �̷���� composition
        ans += "1";
        return;
    }

    // decompostion(0�̳� 1�θ� �̷������ �ʾ��� ��.)
    if(n % 2 == 0 && m % 2 == 0) {
        ans += "D";
        solve_1(x, y, n/2, m/2); // �»��
        solve_1(x, y+m/2, n/2, m/2); // ����
        solve_1(x+n/2, y, n/2, m/2); // ���ϴ�
        solve_1(x+n/2, y+m/2, n/2, m/2); // ���ϴ�
        // N,M ¦���϶��� �ش�
    }
    else if(n % 2 != 0 && m % 2 == 0) {
        ans += "D";
        solve_1(x, y, n/2 + 1, m/2); // �»��
        solve_1(x, y+m/2, n/2 + 1 , m/2); // ����
        solve_1(x+n/2 + 1, y, n/2, m/2); // ���ϴ�
        solve_1(x+n/2 + 1, y+m/2, n/2, m/2); // ���ϴ�
        // N Ȧ�� M ¦��
    }
    else if(n % 2 == 0 && m % 2 != 0) {
        ans += "D";
        solve_1(x, y, n/2, m/2 + 1); // �»��
        solve_1(x, y+m/2 + 1, n/2, m/2); // ����
        solve_1(x+n/2, y, n/2, m/2 + 1); // ���ϴ�
        solve_1(x+n/2, y+m/2 + 1, n/2, m/2); // ���ϴ�
        // N ¦�� M Ȧ��
    }
    else if(n % 2 != 0 && m % 2 != 0) {
        ans += "D";
        solve_1(x, y, n/2 + 1, m/2 + 1); // �»��
        solve_1(x, y + m/2 + 1, n/2 + 1, m/2); // ����
        solve_1(x+n/2 + 1, y, n/2, m/2 + 1); // ���ϴ�
        solve_1(x+n/2 + 1, y+m/2 + 1, n/2, m/2); // ���ϴ�
        // N Ȧ�� M Ȧ��
    }
}

void solve_2(int x,int y,int n,int m) {
    if(dir >= bitmap.size()) {
        return;
    }
    char cmd = bitmap[dir]; // �� loop���� dir �� +1, cmd ���� ���� ����.
    
    if(n == 0 || m == 0) {
        return;
    }

    if(cmd == 'D') {
        if(n % 2 == 0 && m % 2 == 0) {
            dir++;
            solve_2(x, y, n/2, m/2); // �»��
            solve_2(x, y+m/2, n/2, m/2); // ����
            solve_2(x+n/2, y, n/2, m/2); // ���ϴ�
            solve_2(x+n/2, y+m/2, n/2, m/2); // ���ϴ�
            // N,M ¦���϶��� �ش�
        }
        else if(n % 2 != 0 && m % 2 == 0) {
            dir++;
            solve_2(x, y, n/2 + 1, m/2); // �»��
            solve_2(x, y+m/2, n/2 + 1 , m/2); // ����
            solve_2(x+n/2 + 1, y, n/2, m/2); // ���ϴ�
            solve_2(x+n/2 + 1, y+m/2, n/2, m/2); // ���ϴ�
            // N Ȧ�� M ¦��
        }
        else if(n % 2 == 0 && m % 2 != 0) {
            dir++;
            solve_2(x, y, n/2, m/2 + 1); // �»��
            solve_2(x, y+m/2 + 1, n/2, m/2); // ����
            solve_2(x+n/2, y, n/2, m/2 + 1); // ���ϴ�
            solve_2(x+n/2, y+m/2 + 1, n/2, m/2); // ���ϴ�
            // N ¦�� M Ȧ��
        }
        else if(n % 2 != 0 && m % 2 != 0) {
            dir++;
            solve_2(x, y, n/2 + 1, m/2 + 1); // �»��
            solve_2(x, y + m/2 + 1, n/2 + 1, m/2); // ����
            solve_2(x+n/2 + 1, y, n/2, m/2 + 1); // ���ϴ�
            solve_2(x+n/2 + 1, y+m/2 + 1, n/2, m/2); // ���ϴ�
            // N Ȧ�� M Ȧ��
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
        else if(input_mode == 'B') { // �־��� ��Ʈ���� ������, ��Ʈ�� decomposition
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
        else if(input_mode == 'D') { // �־��� ������ ������, ��Ʈ���� ��������.
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
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int T;
int N,M;
char board[105][105];
char spin_copy[105][105];
char slide_copy[105][105];

ifstream fin("spinslide.inp");
ofstream fout("spinslide.out");

void setup() {
    for(int i = 0;i<105;i++) {
        for(int j = 0;j<105;j++) {
            board[i][j] = '.';
            slide_copy[i][j] = '.';
            spin_copy[i][j] = '.';
        }
    }
}

void spin() {
    for(int i = 0;i<N;i++) {
        for(int j = 0;j<N;j++) {
            spin_copy[i][j] = board[N-1-j][i];
        }
    }
    for(int i = 0;i<N;i++) {
        for(int j = 0;j<N;j++) {
            board[i][j] = spin_copy[i][j];
        }
    }

    for(int i = 0;i<N;i++) {
        for(int j =0;j<N;j++) {
            spin_copy[i][j] = '.';
        }
    }
}

void slide() {
    string temp = "";
    string down[105];

    for(int i = 0;i<N;i++) {
        for(int j = N-1;j>=0;j--) {
            if(board[j][i] != '.') {
                temp += board[j][i];
            }
        }
        down[i] = temp; // 하나라도 옮길게 있다면 문자열 붙여서 저장
        temp = "";
    }

    for(int i = 0;i<N;i++) {
        if(down[i].length() > 0) {
            string ttemp = down[i];
            int len = down[i].length();
            int start = N - len; // 여기서부터 밑으로 스트링 붙이면 됌.
            int idx = len-1;
            for(int j = start;j<N;j++) { // down 뒤부터 이어붙이기.
                slide_copy[j][i] = ttemp[idx];
                idx--;
            }
        }
    }

    for(int i = 0;i<N;i++) {
        for(int j = 0;j<N;j++) {
            board[i][j] = slide_copy[i][j];
        }
    }

    for(int i = 0;i<N;i++) {
        for(int j =0;j<N;j++) {
            slide_copy[i][j] = '.';
        }
    }

}

void show(int n) {
    fout << "Case  #" << n+1 << ":" << '\n'; 
    for(int i = 0;i<N;i++) {
        for(int j = 0;j<N;j++) {
            fout << board[i][j];
        }
        fout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);

    fin >> T;
    for(int i = 0;i<T;i++) {
        setup();
        fin >> N >> M;
        string temp;

        for(int i = 0;i<N;i++) {
            fin >> temp;
            for(int j = 0;j<N;j++) {
                board[i][j] = temp[j];
            }
        }

        for(int i = 0;i<M;i++) {
            spin();
            slide();
        }
        
        show(i);
        fout << '\n';
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n,T;
int board[100005];

void reset(int a) {
    for(int i = 0;i<a;i++) {
        board[i] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);

    ifstream fin("gain.inp");
    ofstream fout("gain.out");

    fin >> T;
    for(int i = 0;i<T;i++) {
        fin >> n;

        for(int j = 0;j<n;j++) {
            fin >> board[j];
        }

        sort(board,board+n);

        fout << board[n-1] - board[0] + board[n-2] - board[1] << '\n';
        // �ִ밪 1 - �ּҰ� 1 + �ִ밪 2 - �ּҰ� 2
        // == �ִ밪 1 - �ּҰ� 2 + �ִ밪 2 - �ּҰ� 1

        reset(n);
    }

    fin.close();
    fout.close();

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int T;
int N,M,K;

int main() {
    ifstream fin("grid.inp");
    ofstream fout("grid.out");

    fin >> T;
    while(T--) {
        bool flag = false;
        vector <int> paint;
        int temp;
        fin >> N >> M >> K;

        for(int i = 0;i<K;i++) {
            fin >> temp;
            paint.push_back(temp);
        }

        sort(paint.begin(),paint.end());

        unsigned long long NM;

        if(K == 1) {
            NM = N * M;
            if(NM <= temp) {
                flag = true;
            }
        }
        else { // K > 1
        // N,M에 대해서 짝/홀 여부에 따라 홀수면 나누었을때 몫이 3이상이 있어야함
        // 짝수면 2이상인것만 다 더해서 상대 M이나 N에 대해서 크면 됨.
            int N_cnt = 0;
            int M_cnt = 0;
            bool tri = false;
            for(int i = 0;i<K;i++) {
                if(paint[i] / M >= 2) {
                    if(((paint[i] / M) % 2) != 0) {
                        tri = true;
                    }   
                    N_cnt += paint[i] / M;
                }
            }

            if(N%2 == 0) {
                if(N_cnt >= N) {
                    flag = true;
                }
            }
            else {
                if(N_cnt >= N && tri) {
                    flag = true;
                }
            }

            tri = false;

            for(int i = 0;i<K;i++) {
                if(paint[i] / N >= 2) {
                    if(((paint[i] / N) % 2) != 0) {
                        tri = true;
                    }
                    M_cnt += paint[i] / N;
                }
            }

            if(M%2 == 0) {
                if(M_cnt >= M) {
                    flag = true;
                }
            }
            else {
                if(M_cnt >= M && tri) {
                    flag = true;
                }
            }

        } 

        if(!flag) {
            fout << "No" << '\n';
        }
        else {
            fout << "Yes" << '\n';
        }
    }



    fin.close();
    fout.close();

    return 0;
}
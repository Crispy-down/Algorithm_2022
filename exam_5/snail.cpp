#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#define ll long long
using namespace std;

int T;
ll N,A,B;
ll temp;
ll K;
ll A_pos;
ll B_pos;
ll A_N;
ll B_N;
ll A_x,A_y;
ll B_x,B_y; 
ll func_A,func_B;
ll less_A,less_B;
vector <pair<ll,ll>> start_p;
int dx[4] = {0,1,0,-1}; // 우 하 좌 상
int dy[4] = {1,0,-1,0};


int main() {
    ifstream fin("snail.inp");
    ofstream fout("snail.out");

    fin >> T;

    while(T--) {
        fin >> N >> A >> B;
        A--;
        B--;

        temp = 0;
        K = 0;

        if(N == 2) {
            if(A == B || (abs(A-B) % 2) == 0) {
                fout << "YES" << '\n';
            }
            else {
                fout << "NO" << '\n';
            }
            continue;
        }

        while(true) {
            if(N < K || temp > (N*N) - 1) {
                break;
            }
            if(temp == (N*N) -1) {
                start_p.push_back(make_pair(temp,0));
            }
            else {
                start_p.push_back(make_pair(temp,N-K)); // 시작 수 , 해당 껍질 한변 길이.
            }
            temp += 4 * (N - K) - 4; // 0부터 시작하여서, 각 껍질 시작하는 수 구함.(vector 저장)
            K += 2;
        }

        for(int i = 0;i<start_p.size();i++) {
            if(A >= start_p[i].first) {
                A_pos = i;
                A_N = start_p[i].second;
            }
            if(B >= start_p[i].first) {
                B_pos = i;
                B_N = start_p[i].second;
            }
        }

        A_x = A_pos; // A값이 속한 껍질이 몇번째 인지.(기본 좌표)
        A_y = A_pos;
        B_x = B_pos;
        B_y = B_pos;

        func_A = (A - start_p[A_pos].first) / (A_N - 1); // 우밑좌상 연산 횟수(1번 = y++, 2번 x++ , 3번 y-- , 4번 x--)
        less_A = (A - start_p[A_pos].first) % (A_N - 1); // 연산하고 더 가야하는 횟수  (해당 방향대로, 0번이라면 y++,1번이라면 x++, 2번이라면 y--, 3번이라면 )
        func_B = (B - start_p[B_pos].first) / (B_N - 1); // 우밑좌상 연산 횟수(1번 = y++, 2번 x++ , 3번 y-- , 4번 x--)
        less_B = (B - start_p[B_pos].first) % (B_N - 1);

        if(func_A == 1) {
            A_y += A_N - 1;
            if(less_A > 0) {
                A_x += less_A;       
            }
        }
        else if(func_A == 2) {
            A_x += A_N-1;
            A_y += A_N-1;
            if(less_A > 0) {
                A_y -= less_A;       
            }
        }
        else if(func_A == 3) {
            A_x += A_N-1;
            if(less_A > 0) {
                A_x -= less_A;       
            }
        }
        else {
            A_y += less_A;
        }

        if(func_B == 1) {
            B_y += B_N-1;
            if(less_B > 0) {
                B_x += less_B;       
            }
        }
        else if(func_B == 2) {
            B_x += B_N-1;
            B_y += B_N-1;
            if(less_B > 0) {
                B_y -= less_B;       
            }
        }
        else if(func_B == 3) {
            B_x += B_N-1;
            if(less_B > 0) {
                B_x -= less_B;       
            }
        }
        else {
            B_y += less_B;
        }

        if(abs(A_x - B_x) == abs(A_y - B_y)) {
            fout << "YES" << '\n';
        }
        else {
            fout << "NO" << '\n';
        }

        start_p.clear();

    }


    fin.close();
    fout.close();

    return 0;

}
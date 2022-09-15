#include <iostream>
#include <fstream>
using namespace std;

int T,M,F,N;
int elev;

// 자신이 있는 층을 떠나서,
// 전체 오를수 있는 계단의 칸 수는 최대 M-1
// N을 최대값으로 계속 줄일 수 있다면 최소로 엘리베이터를 이용하는 것이랑 같다
// 따라서, 1층으로 계속 가서 M-1 칸 타고 F층 이동
// N이 M-1 보다 적게 남는다면 한번 더 타면 됌 ( F층으로 복귀 )

int main() {
    ios::sync_with_stdio(false);

    ifstream fin("stairs.inp");
    ofstream fout("stairs.out");

    fin >> T;
    for(int i =0;i<T;i++) {
        fin >> M >> F >> N;
        elev = N / (M-1); // 전체 1층부터 M층 까지 M-1번 N을 줄여나감(elev)
        if(N % (M-1) != 0) { // 그럼에도 남은 층수가 있다면 한번만 더 타면 됌.
            elev++;
        }
        fout << elev << '\n';
    }

    fin.close();
    fout.close();

    return 0;
}
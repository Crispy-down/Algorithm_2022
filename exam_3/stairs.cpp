#include <iostream>
#include <fstream>
using namespace std;

int T,M,F,N;
int elev;

// �ڽ��� �ִ� ���� ������,
// ��ü ������ �ִ� ����� ĭ ���� �ִ� M-1
// N�� �ִ밪���� ��� ���� �� �ִٸ� �ּҷ� ���������͸� �̿��ϴ� ���̶� ����
// ����, 1������ ��� ���� M-1 ĭ Ÿ�� F�� �̵�
// N�� M-1 ���� ���� ���´ٸ� �ѹ� �� Ÿ�� �� ( F������ ���� )

int main() {
    ios::sync_with_stdio(false);

    ifstream fin("stairs.inp");
    ofstream fout("stairs.out");

    fin >> T;
    for(int i =0;i<T;i++) {
        fin >> M >> F >> N;
        elev = N / (M-1); // ��ü 1������ M�� ���� M-1�� N�� �ٿ�����(elev)
        if(N % (M-1) != 0) { // �׷����� ���� ������ �ִٸ� �ѹ��� �� Ÿ�� ��.
            elev++;
        }
        fout << elev << '\n';
    }

    fin.close();
    fout.close();

    return 0;
}
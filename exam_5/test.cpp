#include <iostream>
#define ll long long
using namespace std;

int T;
ll N,A,B;
ll A_x,A_y;
ll B_x,B_y;
ll A_N,B_N; // ���� �� �� ����


int main() {

    cin >> T;

    while(T--) {
        cin >> N >> A >> B;
        A--;
        B--;

        ll temp = 0;
        ll K = 0;
        ll cnt = 0; // �� ��° ��������.

        while(true) {
            if(K > N) {
                break;
            }
            if(A < temp) {
                A_x = cnt;
                A_y = cnt;
                if(K+2 > N && N%2 == 0) { // ������ �Ȳ����� ���(¦��)
                    A_N = 2;
                }
                else if(K+2 > N && N%2 != 0){ // ������ �Ȳ����� ���(Ȧ��)
                    A_N = 0;
                }
            }
            else if(B < temp) {
                B_x = cnt;
                B_y = cnt;
                if(K+2 > N && N%2 == 0) { // ������ �Ȳ����� ���(¦��)
                    A_N = 2;
                }
                else if(K+2 > N && N%2 != 0){ // ������ �Ȳ����� ���(Ȧ��)
                    A_N = 0;
                }
            }

            temp += 4 * ( N - K ) - 4;
            K += 2;
            cnt++;
        }

        cout << A_x << " " << A_y << '\n';
        cout << B_x << " " << B_y << '\n';
    }
}


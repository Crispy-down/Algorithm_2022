#include <iostream>

using namespace std;

int main() {
    string temp = "H";
    temp += "2";
    temp += to_string(123);
    cout << temp;
}
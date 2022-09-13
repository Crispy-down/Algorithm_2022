#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

int N;
int ppl_num;
string num,first,last;
vector<tuple <int,string,string,string>> v;
vector <string> first_n;
vector <string> last_n;

int find_max_length() {
    int temp = 0;
    for(int i = 0;i<first_n.size();i++) {
        if(first_n[i].length() > temp) {
            temp = first_n[i].length();
        }
    }
    return temp;
}

int main() {
    ios::sync_with_stdio(false);

    ifstream fin("test.inp");
    ofstream fout("test.out");

    fin >> N;

    vector <string> str;

    for(int i = 0;i<N;i++) {
        fin >> num >> first >> last;
        ppl_num = stoi(num);

        v.push_back(make_tuple(ppl_num,first,last,num));
        first_n.push_back(first);
        last_n.push_back(last);
        str.push_back(last);
    }

    sort(v.begin(),v.end());

    sort(last_n.begin(),last_n.end());
    sort(str.begin(),str.end());

    last_n.erase(unique(last_n.begin(),last_n.end()), last_n.end()); // 중복제거 후 원본 벡터와 비교


    int leng = find_max_length();
    for(int i = 0 ;i<v.size();i++) {
        int temp = leng - get<1>(v[i]).length();
        fout << get<3>(v[i]) << " " << get<1>(v[i]);
        for(int i = 0;i<temp;i++) {
            fout << " ";
        }
        fout << " " << get<2>(v[i]) << '\n';
    }

    fout << '\n';

    for(int i = 0;i<last_n.size();i++) {
        int word_cnt = count(str.begin(),str.end(),last_n[i]);
        if(word_cnt > 1) {
            fout << last_n[i] << " " << word_cnt << '\n'; // 중복값 1개 이상이면 출력.
        }
    }


    return 0;
}
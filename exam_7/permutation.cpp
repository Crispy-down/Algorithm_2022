#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <utility>
using namespace std;

int T;
int n;
int arr[1002];
int depth[1002];
map <int,pair<int,int>> tree;

// void inorder(int node) {
//     if(tree[node].first > 0) {
//         inorder(tree[node].first);
//     }
//     fout << node << " ";
//     if(tree[node].second > 0) {
//         inorder(tree[node].second);
//     }
// }

void clear(int n) {
    for(int i = 0;i<=n;i++) {
        arr[i] = 0;
        depth[i] = 0;
        tree[i].first = 0;
        tree[i].second = 0;
    }
}

void node_depth(int root) {
    queue <int> q;
    q.push(root);
    depth[root] = 0;
    while(!q.empty()) {
        int cur = q.front(); // root ���� ����
        q.pop();
        for(int nxt : {tree[cur].first , tree[cur].second}) {
            if(nxt <= 0) {
                continue;
            }
            q.push(nxt);
            depth[nxt] = depth[cur] + 1;
        }
    }
}

int build_tree(int start , int end , int K) {
    int root_node = -1;
    int pivot_idx;

    if(K == 1) { // ���� ������ ��� �ϳ��ۿ� ���ٸ� ����.
        return arr[start]; // pivot ��..?
    }
    else if(K == 0) { // ���� ����.
        return -1;
    }

    for(int i = start;i<end;i++) { // �־��� ���� �� �ִ밪 �̾Ƴ�
        if(arr[i] > root_node) {
            root_node = arr[i];
            pivot_idx = i;
        }
    }
    
    int left_node = build_tree(start,pivot_idx,(pivot_idx) - start); // �Ǻ� ���� ���� ������ ��� - ���� ������ �ִ밪 ����
    int right_node = build_tree(pivot_idx + 1,end,end - (pivot_idx+1)); // �Ǻ� ���� ������ ������ ��� - ������ ������ �ִ밪 ����.

    tree[root_node] = make_pair(left_node,right_node); // �ִ밪�� �ڽ� ��� ����.

    return root_node;
}

int main() {
    ifstream fin("permutation.inp");
    ofstream fout("permutation.out");

    fin >> T;

    while(T--) {
        fin >> n;
        int max_ele = -1;

        for(int i = 0;i<n;i++) {
            fin >> arr[i];
            if(max_ele < arr[i]) {
                max_ele = arr[i];
            }
        }

        build_tree(0,n,n);
        node_depth(max_ele);

        for(int i = 0;i<n;i++) {
            fout << depth[arr[i]] << " ";
        }
        fout << '\n';

        clear(n);
    }

    fin.close();
    fout.close();

    return 0; 
}
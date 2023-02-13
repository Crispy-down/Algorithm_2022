#include <bits/stdc++.h>
using namespace std;

struct cmp {
    int operator()(const tuple <int,int,int,int> &a, const tuple <int,int,int,int> &b) {
        if(get<0>(a) == get<0>(b)) {
            return get<3>(a) > get<3>(b); // min heap **
        }
        return get<0>(a) >= get<0>(b); // min heap **
    }
};

// string inp = "mst.inp";
// string out = "mst.out";

// ifstream cin(inp);
// ofstream cout(out);

int n,m; // vertice & edge cnt
int cnt = 0;
int ans = 0;

tuple <int,int,int,int> edge[100005]; // cost, u , v , edge_order
vector <int> parent(10005,-1); // for union cind
vector <int> K_edge; // 크루스칼 알고리즘 간선

vector <tuple<int,int,int>> adj[10005]; // 프림 알고리즘을 위한 비용,정점2,간선 순서
vector <int> P_edges; //프림 알고리즘 간선
bool chk[10005]; // i번째 정점이 MST에 속해 있는가
priority_queue < tuple <int,int,int,int> , vector <tuple<int,int,int,int>>, cmp > pq;

void reset() {
    cnt = 0;
    ans = 0;
    for(int i = 0;i<=n;i++) {
        chk[i] = 0;
    }
    while(!P_edges.empty()) {
        P_edges.pop_back();
    }
    while(!pq.empty()) {
        pq.pop();
    }
}

bool compare(tuple<int,int,int,int> a , tuple <int,int,int,int> b) {
    if(get<0>(a) == get<0>(b)) {
        return get<3>(a) < get<3>(b);
    }
    return get<0>(a) < get<0>(b);
}

int cind(int x) {
    if(parent[x] < 0) {
        return x;
    }
    return parent[x] = cind(parent[x]);
}

bool isUnion(int u,int v) {
    u = cind(u);
    v = cind(v);
    if(u == v) {
        return true;
    }
    if(parent[u] > parent[v]) { // union-by-rank
    // puts lower height tree to higher height tree
        swap(u,v);
    }
    parent[u] += parent[v];
    parent[v] = u;
    return false;
}

void Prim(int start) {
    chk[start] = 1; // visited
    for(auto nxt : adj[start]) { // cost , v1(from) , v2(to) , i(order)
        pq.push(make_tuple(get<0>(nxt),start,get<1>(nxt),get<2>(nxt)));
    }

    while(cnt < n - 1) {
        int cost , a , b, i;
        tie(cost,a,b,i) = pq.top();
        pq.pop();
        if(chk[b]) {
            continue;
        }
        ans += cost;
        P_edges.push_back(i);
        chk[b] = 1;
        cnt++;
        for(auto nxt : adj[b]) {
            if(!chk[get<1>(nxt)]) {
                pq.push(make_tuple(get<0>(nxt),b,get<1>(nxt),get<2>(nxt)));
            }
        }
    }

    cout << "Tree edges by Prim algorithm with starting vertex " << start << ": " << ans << '\n';

    for(int i = 0;i<P_edges.size();i++) {
        cout << P_edges[i] << '\n';
    }
}


int main() {
    cin >> n >> m;

    int first = 0;
    int second = n/2;
    int third = n-1;

    // edge count starts in 0
    for(int i = 0;i<m;i++) {
        int u,v,cost; // u - v cost w
        cin >> u >> v >> cost;
        edge[i] = make_tuple(cost,u,v,i); // i for selected edge
        adj[u].push_back(make_tuple(cost,v,i));
        adj[v].push_back(make_tuple(cost,u,i));
    }

    sort(edge,edge + m,compare);

    for(int k = 0;k<m;k++) {
        int u,v,cost,i;
        tie(cost,u,v,i) = edge[k];
        if(isUnion(u,v)) { // same root
            continue;
        }
        ans += cost;
        K_edge.push_back(i);
        cnt++;
        if(cnt == n-1) {
            break;
        }
    }

    cout << "Tree edges by Kruskal algorithm: " << ans << '\n';
    for(int i = 0;i<K_edge.size();i++) {
        cout << K_edge[i] << '\n';
    }

    ///////////// Kruskal

    reset();
    Prim(first);

    reset();
    Prim(second);

    reset();
    Prim(third);

    //////////// Prim
    
    return 0;
}
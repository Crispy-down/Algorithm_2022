#include <bits/stdc++.h>
using namespace std;

int n,m;
int board[202][202];
int cost[202][202];
string path[202][202];
vector <pair<int,int>> path_info;

int main() {
    ifstream fin("gridpath.inp");
    ofstream fout("gridpath.out");

    fin >> n >> m;

    fill(&cost[0][0],&cost[201][202],-2);


    for(int i = 1;i<=n;i++) {
        for(int j = 1;j<=m;j++) {
            fin >> board[i][j];
        }
    }

    for(int i = 1;i<=n;i++) {
        for(int j = 1;j<=m;j++) {
            if(i == 1 && j == 1) {
                cost[i][j] = board[i][j];
                path[i][j] = "start";
                continue;
            }
            if(board[i][j] == -1) {
                cost[i][j] = -1;
                path[i][j] = "NONE";
                continue;
            }
            if(cost[i][j-1] < 0 && cost[i-1][j] < 0) {
                cost[i][j] = -1;
                path[i][j] = "NONE";
            }
            else if(cost[i][j-1] < 0 && cost[i-1][j] > 0) { //À§¿¡¼­ ¿È.
                cost[i][j] = cost[i-1][j] + board[i][j];
                path[i][j] = "up";
            }
            else if(cost[i-1][j] < 0 && cost[i][j-1] > 0 ) { //¿À¸¥ÂÊ¿¡¼­ ¿È.
                cost[i][j] = cost[i][j-1] + board[i][j];
                path[i][j] = "left";
            }
            else {
                if(cost[i-1][j] < cost[i][j-1]) { // À§¿¡¼­ ¿È
                    cost[i][j] = cost[i-1][j] + board[i][j]; 
                    path[i][j] = "up";
                }
                else if(cost[i-1][j] > cost[i][j-1]) { // ¿À¸¥ÂÊ¿¡¼­ ¿È
                    cost[i][j] = cost[i][j-1] + board[i][j];
                    path[i][j] = "left";
                }
                else if(cost[i-1][j] == cost[i][j-1]) {
                    cost[i][j] = cost[i][j-1] + board[i][j];
                    path[i][j] = "up";
                }
            }
        }
    }

    if(cost[n][m] == -1) {
        fout << "No path.";
        return 0;
    }
    else {
        fout << cost[n][m] << '\n';
    }


    int cur_x = n;
    int cur_y = m;

    while(true) {
        if(path[cur_x][cur_y] == "left") {
            path_info.push_back(make_pair(cur_x,cur_y));
            cur_y -= 1;
        }
        else if(path[cur_x][cur_y] == "up") {
            path_info.push_back(make_pair(cur_x,cur_y));
            cur_x -= 1;
        }
        else if(path[cur_x][cur_y] == "start") {
            path_info.push_back(make_pair(cur_x,cur_y));
            break;
        }
    }

    for(int i = path_info.size()-1;i>=0;i--) {
        fout << "(" << path_info[i].first - 1 << " " << path_info[i].second - 1 << ")" << '\n';
    }


    fin.close();
    fout.close();
}
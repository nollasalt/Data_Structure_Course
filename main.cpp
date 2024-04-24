#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> node;

void solve(int source,vector<vector<node>> &graph);
const int pMax=100,pMin=0;
int main(){
    vector<vector<node>> graph;
    int source = 0;
    solve(source,graph);
    return 0;
}

void dfs(int fa,int u,int p,vector<vector<node>> &graph)
{
    static
    for(auto temp:graph[u])
    {
        int &v=temp.first;
        int &weight=temp.second;
        if(v==fa) continue;
        if(p-weight<pMin){

        }
    }
}
void solve(int source,vector<vector<node>> &graph)
{

}
#include <bits/stdc++.h>
using namespace std;

struct btnode {//用于分支定界的子集树
    btnode* parent;//指向父节点
    int press;//
    int level;//子集树层级
    bool bstHere;//是否放放大器
    int bstCnt;//优先级 从根到节点x的路径上的bst个数

    btnode() {
        parent = nullptr;
        press = 0; level = 0; bstHere = false;
        bstCnt = 0;
    }

    btnode(int pres, int lev, btnode* par = nullptr, int bstn = 0) {
        parent = par;
        press = pres; level = lev;
        bstCnt = bstn;
        bstHere = false;
    }

};

class Edge {
public:
    int to;// 终点编号
    int cost;// 长度
    Edge(int to, int cost) : to(to), cost(cost) {}
    ~Edge() {}
};

class Node {
public:
    vector<Edge> edges;//记录所有出边
    int press;
    bool bstHere;
    int maxToCost;
    Node() {
        press = 0;
        bstHere = false;
        edges.clear();
        maxToCost = 0;
    }
    ~Node() {}
};

struct cmp
{
    bool operator () (const btnode* p1, const btnode* p2) {
        return p1->bstCnt > p2->bstCnt;
    }
};

class DAG {
private:

    int Pmin, Pmax;//
    vector<Node> nodes;// 邻接表
    vector<int> inDegree;
    vector<int> top;//拓扑序列
    vector<bool> bstHere;//是否要放在这
    priority_queue<btnode*, vector<btnode*>, cmp> pq;//最小堆


public:
    int n, m;//顶点数 边
    DAG() {
        cin >> n >> m >> Pmax;
        Pmin = 0;
        maxAns = INT_MAX;
        nodes.clear();
        inDegree.resize(n + 1, 0);
        top.resize(n + 1, 0);
        bstHere.resize(n + 1, false);

        for (int i = 0; i <= n; i++)
            nodes.emplace_back(Node());
        for (int i = 1; i <= m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            nodes[u].edges.emplace_back(v, w);
            //修改入度
            inDegree[v]++;
            nodes[u].maxToCost = max(nodes[u].maxToCost, w);
        }
        nodes[1].press = Pmax;
        bstHere[1] = true;
    }
    ~DAG() {}
    int maxAns;//最优解 数目

    void topsort();//用拓扑排序 来确定先后关系
    void output_bst();//输出booster
    void backTrace(int level, int cnt);//回溯解决
    void branchBound();//分支定界解决

};


void DAG::topsort()
{
    int cnt = 1;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        top[cnt++] = u;//排序
        for (auto e : nodes[u].edges) {
            if (--inDegree[e.to] == 0)
                q.push(e.to);
        }
    }
}


void DAG::backTrace(int level, int cnt)
{
    if (level >= n) {
        maxAns = min(cnt, maxAns);
        for (int i = 1; i <= n; i++) {
            bstHere[i] = false;
            bstHere[i] = nodes[i].bstHere;
        }
        return;
    }

    int u = top[level];
    int maxPress = -1;
    for (int k = 1; k < level; k++) {
        for (auto& x : nodes[top[k]].edges) {
            if (x.to == u)
                maxPress = max(maxPress, nodes[top[k]].press - x.cost);
        }
    }

    if (maxPress >= Pmax) {
        backTrace(level + 1, cnt);
        return;
    }
    if(maxPress - nodes[u].maxToCost >= Pmin)
    {
        nodes[u].press = maxPress;
        nodes[u].bstHere = false;
        backTrace(level + 1, cnt);
    }
    cnt++;
    nodes[u].press = Pmax;
    nodes[u].bstHere = true;
    if (cnt < maxAns)
        backTrace(level + 1, cnt);
}


void DAG::branchBound()
{
    btnode* node = new btnode(Pmax, 2);
    int level = 2;
    while (level < n)
    {
        int vert = top[level];
        int maxPress = -1;

        for (int k = 1; k < level ; k++) {
            for (auto& e : nodes[top[k]].edges) {
                if (e.to == vert) {
                    btnode* p = node;
                    for (int j = level - 1; j > k; j--)
                        p = p->parent;

                    maxPress = max(maxPress, p->press - e.cost);
                }
            }
        }

        if (maxPress - nodes[vert].maxToCost >= Pmin) {
            btnode* t = new btnode(maxPress, level + 1, node, node->bstCnt);
            pq.push(t);
        }
        btnode* tt = new btnode(Pmax, level + 1, node, node->bstCnt + 1);
        tt->bstHere = true;
        pq.push(tt);

        node = pq.top(); pq.pop();
        level = node->level;
    }
    maxAns = node->bstCnt;

    btnode* p = node;
    while (p) {
        bstHere[top[p->level - 1]] = p->bstHere;
        p = p->parent;
    }
}

void DAG::output_bst()
{
    for (int i = 1; i <= n; i++) {
        if (bstHere[i])
            cout << "node " << i << " ";
    }
}
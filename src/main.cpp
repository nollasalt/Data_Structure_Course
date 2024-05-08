#include<bits/stdc++.h>
#include "solve.h"

using namespace std;


signed main() {
    //string pathOut="out/branchBound.ans";
    string pathOut="out/backTrace.ans";
    freopen(pathOut.c_str(),"w",stdout);
    for (int i = 1; i <= 100; ++i) {
        string pathIn="in/test";
        pathIn+=to_string(i);
        pathIn+=".in";
        freopen(pathIn.c_str(),"r",stdin);
        DAG g;
        g.topsort();
        typedef std::chrono::high_resolution_clock Clock;
        auto t1 = Clock::now();//计时开始
        //g.backTrace(2, 0);
        g.branchBound();
        //g.output_bst();
        cout<<g.maxAns<<endl;
        auto t2 = Clock::now();//计时结束
        //std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << "ns" << endl;
    }
}
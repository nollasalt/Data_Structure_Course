#include<bits/stdc++.h>
#include "solve.h"

using namespace std;


signed main() {
    
    DAG g;
    g.topsort();
//    g.backtracking(1,0);
//    g.output_bst();
//    cout<<"\n########"<<endl;
    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();//计时开始
    g.branch_bound();
    g.output_bst();
    auto t2 = Clock::now();//计时结束
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << "ns" << endl;
}
#include<bits/stdc++.h>
#include "solve.h"

using namespace std;


signed main() {
    DAG g;
    g.topsort();
    g.backtracking(1,0);
    g.output_bst();
}
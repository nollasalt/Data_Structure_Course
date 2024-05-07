#include<bits/stdc++.h>
#include "solve.h"

using namespace std;


signed main() {
    DAG g;
    g.topsort();
    g.branch_bound();
    g.output_bst();
}
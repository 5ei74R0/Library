#include <bits/stdc++.h>
using namespace std;

/*UnionFind--------------------------*/
class UnionFind {
using i32 = int_fast32_t;
private:
    std::vector<i32> parent;
    std::vector<i32> siz;

public:
    UnionFind(i32 sz): parent(sz), siz(sz, 1) {
        for(i32 i = 0; i < sz; ++i) parent[i] = i;
    }
    void init(i32 sz) {
        for(i32 i = 0; i < sz; ++i) parent[i] = i;
    }
    /*Member Func------*/
    /*return root id*/
    i32 root(i32 x) {
        while(parent[x] != x) {
            x = parent[x] = parent[parent[x]];
        }
        return x;
    }
    /*merge two groups*/
    bool merge(i32 x, i32 y) {
        x = root(x);
        y = root(y);
        if(x == y) return false;
        //Merge Tech
        if (siz[x] < siz[y]) swap(x,y);
        siz[x] += siz[y];
        parent[y] = x;
        return true;
    }
    /*同じ集合にあるか*/
    bool issame(i32 x, i32 y) {
        return (root(x) == root(y));
    }
    /*xの属する集合の大きさ*/
    i32 size(i32 x) {
        return siz[root(x)];
    }
};

/*-----------------------------------*/
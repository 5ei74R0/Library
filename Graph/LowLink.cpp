//
// Created by OtsuKotsu on 2020/07/27.
//
// LowLink
// sorted = true の時のみbridges, articulation_pointsをソートする(default: false)
// is_bridge(), is_articulation_point() は
// sorted = trueの時のみ可能で、 O(logN)で動く
//

#include <bits/stdc++.h>


/* LowLink */
class lowLink {
public:
    using i32 = int_fast32_t;
    std::vector<i32> ord, low, articulation_points;
    std::vector<std::pair<i32, i32>> bridges;
    const std::vector<std::vector<i32>> &G;
private:
    std::vector<bool> seen;
    bool sorted = false;

    i32 inner_dfs(i32 u = 0, i32 p = -1, i32 k = 0) {
        seen[u] = true;
        low[u] = ord[u] = k;
        bool is_ar_pnt = false;
        for(const auto &v : G[u]) {
            if(!seen[v]) {
                k = inner_dfs(v, u, k+1);
                low[u] = std::min(low[u], low[v]);
                if(k != 1 && ord[u] <= low[v]) is_ar_pnt = true;
                if(ord[u] < low[v]) bridges.emplace_back(std::min(u, v), std::max(u, v));
            }
            else if(v != p) low[u] = std::min(low[u], ord[v]);
        }
        if(k == 1 && G[ord[0]].size() > 1) is_ar_pnt = true;
        if(is_ar_pnt) articulation_points.push_back(u);
        return k;
    }
public:
    explicit lowLink(const std::vector<std::vector<i32>> &graph, bool sort_Bridges_and_ArticulationPoints = false):
            ord(graph.size()), low(graph.size()), seen(graph.size()), sorted(sort_Bridges_and_ArticulationPoints), G(graph)
    {
        inner_dfs();
        if(sorted) {
            std::sort(bridges.begin(), bridges.end());
            std::sort(articulation_points.begin(), articulation_points.end());
        }
    }

    bool is_bridge(const i32 &a, const i32 &b) {
        if(!sorted) {
            std::cout << "error: member 'bridges' is not sorted";
            return false;
        }
        std::pair<i32, i32> p = std::make_pair(std::min(a, b), std::max(a, b));
        return p == *std::lower_bound(bridges.begin(), bridges.end(), p);
    }
    bool is_articulation_point(const i32 &a) {
        if(!sorted) {
            std::cout << "error: member 'articulation_points' is not sorted";
            return false;
        }
        return a == *std::lower_bound(articulation_points.begin(), articulation_points.end(), a);
    }
};



/* MAIN */
signed main(){
    using namespace std;
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int_fast32_t n,m, a,b; cin >> n >> m;
    vector<vector<int_fast32_t >> g(n);
    for(int i = 0; i < m; ++i) {
        cin >> a >> b;
        g[--a].push_back(--b);
        g[b].push_back(a);
    }

    lowLink l(g, true);

    for(auto val : l.articulation_points) {
        cout << val << '\n';
    }

    for(int i = 0; i < n; ++i) {
        if(l.is_articulation_point(i)) {
            cout << i << " is articulation point" << '\n';
        }
    }

    for(auto p : l.bridges) {
        cout << p.first << ' ' << p.second << '\n';
    }

    for(int i = 0; i < n-1; ++i) for(int j = i+1; j < n; ++j) {
            if(l.is_bridge(j, i)) {
                cout << i << '-' << j << " is bridge" << '\n';
            }
        }

    cout << "=========" << '\n';

    for(int i = 0; i < n; ++i) {
        cout << l.ord[i] << ' ' << l.low[i] << '\n';
    }
}


/*  Test Case
10 11
1 2
2 3
2 4
2 5
4 5
1 6
6 7
7 8
7 9
9 10
6 10
 */
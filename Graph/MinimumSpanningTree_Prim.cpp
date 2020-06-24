#include<bits/stdc++.h>


/* GRAPH_TEMPLATE ===========================================*/
template<typename T>
struct Edge {
    int_fast32_t to;  // 辺の行き先
    T cost;  // 辺の重み
    Edge(int_fast32_t t, T w): to(t), cost(w) {}
};

template<typename T = int_fast32_t>
using W_Graph = std::vector<std::vector<Edge<T>>>;  // 重み付きグラフ
using Graph = std::vector<std::vector<int_fast32_t>>;  // 通常グラフ
template<typename T = int_fast32_t>
using Matrix = std::vector<std::vector<T>>;  // 隣接行列(使わなさそう...)


/* Minimum Spanning Tree ======================*/
/* Prim's Algorithm */
// 最小全域木を構築する 返り値はpair<総コスト, MST>
template<class T>
std::pair<T, W_Graph<T>> Prim(W_Graph<T> &G) {
    T RetCost = 0;
    W_Graph<T> MST(G.size());
    std::vector<bool> used(G.size(), false);

    using Tup = std::tuple<T, int_fast32_t, int_fast32_t>;
    std::priority_queue<Tup, std::vector<Tup>, std::greater<Tup>> que;
    que.emplace(0, 0, 0);

    while(!que.empty()) {
        T cost;
        int_fast32_t v;  // parent
        int_fast32_t u;  // vertex focused on
        tie(cost, u, v) = que.top();
        que.pop();
        if(used[u]) continue;
        used[u] = true;
        RetCost += cost;
        if(u != v) {
            MST[v].emplace_back(u, cost);
            MST[u].emplace_back(v, cost);
        }
        for(auto &edge : G[u]) {
            que.emplace(edge.cost, edge.to, u);
        }
    }
    return(make_pair(RetCost, MST));
}

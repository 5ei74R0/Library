#include<bits/stdc++.h>

/*GRAPH_TEMPLATE=============================*/
template<typename T>
class Edge {
public:
    int srch; //searched?探索状態記録「null = -1」
    int to; //辺の行き先
    T cost; //辺の重み
    Edge(int t, T w) : srch(-1), to(t), cost(w) {}
    Edge(int t, T w, int src) : srch(src), to(t), cost(w) {}
};
template<typename T>
using W_Graph = std::vector<std::vector<Edge<T>>>;   //重み付きグラフ
using Graph = std::vector<std::vector<int>>;         //通常グラフ
template<typename T>
using Matrix = std::vector<std::vector<T>>;          //隣接行列(使わなさそう...)

/*Minimum Spanning Tree======================*/
/*Prim's Algorithm===========================*/
// 最小全域木を構築する 返り値はpair<総コスト, MST>
template<class T>
std::pair<T, W_Graph<T>> Prim(W_Graph<T> &G) {
    T RetCost = 0;
    W_Graph<T> MST(G.size());
    std::vector<bool> used(G.size(), false);

    using P = std::tuple<T, int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    que.emplace(0, 0, 0);

    while(!que.empty()) {
        T cost;
        int v;  // parent
        int u;  // vertex focused on
        tie(cost, u, v) = que.top();
        que.pop();
        if(used[u]) continue;
        used[u] = true;
        RetCost += cost;
        if(u!=v) {
            MST[v].push_back(Edge<T>(u, cost));
            MST[u].push_back(Edge<T>(v, cost));
        }
        for(auto &edge : G[u]) {
            que.emplace(edge.cost, edge.to, u);
        }
    }
    return(make_pair(RetCost, MST));
}

int main() {
    return 0;
}
#include <bits/stdc++.h>


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


/* Warshall Floyd ===========================================*/
/*隣接行列表現でi==jの要素を0、隣接している部分を重みで、他をinfで初期化しておく*/
template<class T>
void Warshall_Floyd(Matrix<T> &G, T inf) {
    for(int k = 0; k < G.size(); k++) {
        for(int i = 0; i < G.size(); i++) {
            for(int j = 0; j < G.size(); j++) {
                if(G[i][k] == inf || G[k][j] == inf) continue;
                G[i][j] = std::min(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
}

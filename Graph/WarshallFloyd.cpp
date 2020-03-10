#include <bits/stdc++.h>

/*GRAPH_TEMPLATE=============================================*/
template<typename T>
class Edge {
public:
    int src;  // source 状態記録「null = -1」
    int to;  // 辺の行き先
    T cost;  // 辺の重み
    Edge(int t, T w) : src(-1), to(t), cost(w) {}
    Edge(int t, T w, int src) : src(src), to(t), cost(w) {}
};
template<typename T>
using W_Graph = std::vector<std::vector<Edge<T>>>;   //重み付きグラフ
using Graph = std::vector<std::vector<int>>;         //通常グラフ
template<typename T>
using Matrix = std::vector<std::vector<T>>;          //隣接行列(使わなさそう...)



/*Warshall Floyd=============================================*/

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

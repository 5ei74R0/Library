#include <bits/stdc++.h>


/* GRAPH_TEMPLATE */
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



/* Use ======================================================*/
signed main() {

    size_t n; std::cin >> n;

    W_Graph<double> weighted_graph(n);  // doubleの重みをもった重み付きグラフ
    for(int i = 0; i < n; i++) {  // build weighted_graph
        int from, to;
        double cost;
        std::cin >> from >> to >> cost;
        weighted_graph[from].emplace_back(to, cost);
    }

    Graph graph(n);  // 普通のグラフ
    for(int i = 0; i < n; i++) { // build graph
        int from, to;
        std::cin >> from >> to;
        graph[from].push_back(to);
    }

    Matrix<> matrix(n);  // 隣接行列表現
    for(int i = 0; i < n; ++i) {  // build matrix
        int u, v;
        double cost;
        std::cin >> u >> v >> cost;
        matrix[u][v] = matrix[v][u] = cost;
    }
}

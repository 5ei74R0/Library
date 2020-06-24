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


/* Dijkstra(Basic) ========================================*/
template<class T>
std::vector<T> Dijkstra(W_Graph<T> &graph, int_fast32_t start_index) {
    constexpr auto infinity = std::numeric_limits<T>::max();
    std::vector<T> min_dist(graph.size(), infinity);

    using P = std::pair<T, int_fast32_t>;  // std::pair< DistFromStartingPoint, IndexOfVertex >
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    min_dist[start_index] = 0;
    que.emplace(min_dist[start_index], start_index);  //StartingPoint

    while(!que.empty()) {
        T dist;
        int_fast32_t index;
        tie(dist, index) = que.top();
        que.pop();
        if(dist > min_dist[index]) continue;

        for(auto &edge : graph[index]) {
            auto new_dist = dist + edge.cost;
            // compare the length of each route and change min_dist[edge.to]
            if(new_dist >= min_dist[edge.to]) continue;
            min_dist[edge.to] = new_dist;
            que.emplace(min_dist[edge.to], edge.to);
        }
    }
    return min_dist;
}
#include <bits/stdc++.h>
// using namespace std;

/*GRAPH_TEMPLATE=============================================*/
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

/*Dijkstra(Basic)========================================*/
template<class T>
std::vector<T> Dijkstra(W_Graph<T> &G, int s) {
    const auto infinity = std::numeric_limits<T>::max();
    std::vector<T> min_dist(G.size(), infinity);

    using P = std::pair<T, int>; //pair<DistFromStartingPoint, IndexOfVertex>
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    min_dist[s] = 0;
    que.emplace(min_dist[s], s);  //StartingPoint

    while(!que.empty()) {
        T dist;
        int index;
        tie(dist, index) = que.top();
        que.pop();
        if(dist > min_dist[index]) continue;

        for(auto &edge : G[index]) {
            auto new_dist = dist + edge.cost;
            //compare the length of each route and change min_dist[edge.to]
            if(new_dist >= min_dist[edge.to]) continue;
            min_dist[edge.to] = new_dist;
            que.emplace(min_dist[edge.to], edge.to);
        }
    }
    return min_dist;
}
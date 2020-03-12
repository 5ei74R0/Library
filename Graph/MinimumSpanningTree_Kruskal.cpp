#include <bits/stdc++.h>
/*GRAPH_TEMPLATE*/
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



/* Kruskal's Algorithm */

template <typename T>
std::pair<T, W_Graph<T>> Kruskal (W_Graph<T> &G, int NumberOfTrees = 1) {
    std::vector<int> forest;
    std::vector<int> siz(G.size(), 1);
    W_Graph<T> MST(G.size());
    T TOTAL_COST = 0;
    int num_of_trees = G.size();

    for(int i = 0; i < G.size(); ++i) forest.push_back(i);
    std::vector<std::tuple<T, int, int>> edges;
    for(int u = 0; u < G.size(); ++u) for(auto v : G[u]) edges.emplace_back(v.cost, u, v.to);
    std::sort(edges.begin(), edges.end());

    for(auto e : edges) {
        if(num_of_trees == NumberOfTrees) break;
        int U, V; T cost;
        std::tie(cost, U, V) = e;
        int u = U, v = V;
        u = [&]() {while(forest[u] != u) {u = forest[u] = forest[forest[u]];} return u;}();
        v = [&]() {while(forest[v] != v) {v = forest[v] = forest[forest[v]];} return v;}();
        if(forest[u] == forest[v]) continue;
        if(siz[u] < siz[v]) std::swap(u, v);
        siz[u] += siz[v];
        forest[v] = u;
        --num_of_trees;
        MST[U].push_back(Edge<T>(V, cost));
        MST[V].push_back(Edge<T>(U, cost));
        TOTAL_COST += cost;
    }
    return std::make_pair(TOTAL_COST, MST);
}



/*
 *  Verify
 *  "finals" (JOI 2010 Spring Training Camp)
 *  https://atcoder.jp/contests/joisc2010/tasks/joisc2010_finals
 */

int main() {
    using namespace std;

    int n,m,k; cin >> n >> m >> k;
    W_Graph<int> city(n);
    while(m--) {
        int a,b,c; cin >> a >> b >> c;
        --a, --b;
        city[a].push_back(Edge<int>(b, c));
        city[b].push_back(Edge<int>(a, c));
    }
    auto K = Kruskal(city, k);
    cout << K.first << '\n';
}
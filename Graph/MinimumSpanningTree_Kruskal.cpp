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


/* Kruskal's Algorithm */
// return std::pair<総コスト, MST>
template <typename T>
std::pair<T, W_Graph<T>> Kruskal (W_Graph<T> &graph, int_fast32_t NumberOfTrees = 1) {
    std::vector<int_fast32_t> forest;
    std::vector<int_fast32_t> siz(graph.size(), 1);
    W_Graph<T> MST(graph.size());
    T total_cost = 0;
    int_fast32_t num_of_trees = graph.size();

    for(int_fast32_t i = 0; i < graph.size(); ++i) forest.push_back(i);
    std::vector<std::tuple<T, int_fast32_t, int_fast32_t>> edges;
    for(int_fast32_t u = 0; u < graph.size(); ++u) for(auto v : graph[u]) edges.emplace_back(v.cost, u, v.to);
    std::sort(edges.begin(), edges.end());

    for(auto e : edges) {
        if(num_of_trees == NumberOfTrees) break;
        int_fast32_t U, V; T cost;
        std::tie(cost, U, V) = e;
        int_fast32_t u = U, v = V;
        u = [&]() {while(forest[u] != u) {u = forest[u] = forest[forest[u]];} return u;}();
        v = [&]() {while(forest[v] != v) {v = forest[v] = forest[forest[v]];} return v;}();
        if(forest[u] == forest[v]) continue;
        if(siz[u] < siz[v]) std::swap(u, v);
        siz[u] += siz[v];
        forest[v] = u;
        --num_of_trees;
        MST[U].push_back(Edge<T>(V, cost));
        MST[V].push_back(Edge<T>(U, cost));
        total_cost += cost;
    }
    return std::make_pair(total_cost, MST);
}



/*
 *  Verify
 *  "finals" (JOI 2010 Spring Training Camp)
 *  https://atcoder.jp/contests/joisc2010/tasks/joisc2010_finals
 */

signed main() {
    using namespace std;

    int_fast32_t n,m,k; cin >> n >> m >> k;
    W_Graph<int_fast32_t> city(n);
    while(m--) {
        int_fast32_t a,b,c; cin >> a >> b >> c;
        --a, --b;
        city[a].push_back(Edge<int_fast32_t>(b, c));
        city[b].push_back(Edge<int_fast32_t>(a, c));
    }
    auto K = Kruskal(city, k);
    cout << K.first << '\n';
}

//
// Created by OtsuKotsu on 2020/08/07.
//
// Maximum Flow
// Ford Fulkerson's Method
// depedency: ../GraphTemplate.cpp
//

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


/* Ford-Fulkerson */
class FordFulkerson {
    using i32 = int_fast32_t;
private:
    std::vector<std::vector<Edge<i32>>> Graph;
    std::vector<bool> used;
    i32 dfs(i32 v, i32 end_vertex, i32 flow) {
        if(v == end_vertex) return flow;
        used[v] = true;
        for (Edge<i32>& e : Graph[v]) {
            i32& capacity = e.cost;
            if(!used[e.to] && capacity > 0) {
                i32 d = dfs(e.to, end_vertex, std::min(flow, capacity));
                if(d > 0) {
                    capacity -= d;
                    Graph[e.to].emplace_back(v, d);
                    return d;
                }
            }
        }
        return 0;
    }

public:
    explicit FordFulkerson(const std::vector<std::vector<Edge<i32>>>& graph)
            : Graph(graph), used(graph.size()) {}

    i32 execute(i32 start_vertex, i32 end_vertex) {
        i32 max_flow = 0;
        while (true) {
            used.assign(Graph.size(), false);
            i32 flow = dfs(start_vertex, end_vertex, std::numeric_limits<i32>::max());
            if(flow == 0) return max_flow;
            max_flow += flow;
        }
    }
};

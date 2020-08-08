//
// Created by OtsuKotsu on 2020/08/08.
//
// Maximum Flow
// Dinic's Method
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


/* Dinic */
template<typename T>
class Dinic {
    using i32 = int_fast32_t;
private:
    std::vector<std::vector<Edge<T>>> Graph;
    std::vector<i32> level;
    std::vector<i32> iter;

    void bfs(i32 start_vertex) {
        level.assign(Graph.size(), -1);
        std::queue<T> que;
        level[start_vertex] = 0;
        que.push(start_vertex);
        while(que.size()) {
            i32 v = que.front(); que.pop();
            for(Edge<T>& e : Graph[v]) {
                T capacity = e.cost;
                if(capacity > 0 && level[e.to] == -1) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    T dfs(i32 v, i32 end_vertex, T flow) {
        if(v == end_vertex) return flow;
        for(auto e = (Graph[v].begin() + iter[v]); e != Graph[v].end(); ++e) {
            T& capacity = e->cost;
            if(capacity > 0 && level[v] < level[e->to]) {
                T d = dfs(e->to, end_vertex, std::min<T>(capacity, flow));
                if(d > 0) {
                    capacity -= d;
                    Graph[e->to].emplace_back(v, d);
                    return d;
                }
            }
        }
        return 0;
    }

public:
    explicit Dinic(const std::vector<std::vector<Edge<T>>>& graph)
            : Graph(graph), level(graph.size(), -1), iter(graph.size()) {}

    T execute(i32 start_vertex, i32 end_vertex) {
        T max_flow = 0;
        while(true) {
            bfs(start_vertex);
            if(level[end_vertex] == -1) return max_flow;
            iter.assign(Graph.size(), 0);
            T flow;
            while(true) {
                flow = dfs(start_vertex, end_vertex, std::numeric_limits<T>::max());
                if(flow == 0) break;
                max_flow += flow;
            }
        }
    }
};